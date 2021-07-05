#include "Lighting.h"
#include "utilities.h"
#include "LightComputations.h"
#include "Color.h"
#include "World.h"

//#define NDEBUG
#include <cassert>

namespace Lighting
{
    Color color_at(const World &world, const Ray &ray, bool calc_shadow, int remaining)
    {
        // get intersection list by intersection the ray in the world
        const auto list = world.intersect(ray);

        // get the first intersection
        const auto first_inter = Intersection::get_hit(list);

        if (!first_inter.has_value()) // if no intersection return black
            return Color(0, 0, 0);

        // compute the necessary values for Phong shading
        LightComputations comps ( first_inter.value() , ray, list  );

        return shade_hit( world , comps , calc_shadow , remaining );
    }


    Color shade_hit ( const World &world , const LightComputations &comps , bool calc_shadow , int remaining )
    {
        bool in_shadow = false;
        if ( calc_shadow )
            in_shadow = Lighting::is_shadowed( world , comps.over_point );

        Color surface_color = get_surface_color( world.getLight() , comps , in_shadow);
        Color reflected_color = get_reflected_color(world, comps, remaining );
        Color refracted_color = get_refracted_color( world , comps , remaining );

        const auto &mat = comps.object.material ;
        if ( mat.reflectance > 0 && mat.transparency > 0 ) // use Schlick's approx in this case
        {
            float factor = get_schlick_factor( comps );
            return surface_color +  (reflected_color * factor) + (refracted_color * ( 1 - factor )) ;
        }
        else
        {
            return surface_color + reflected_color + refracted_color ;
        }
    }

    Color get_surface_color ( const Light &light , const LightComputations &comps , bool in_shadow )
    {
        Color base_color = comps.object.material.color * light.intensity; // base color made up of the light color and material color

        // calculate lightv as vector from point to the light source
        Vector lightv = light.position - comps.surface_point ;
        lightv.normalize();

        Color ambient = base_color * comps.object.material.ambient ;

        // lightv and normal are both normalized vectors
        float cosine = lightv * comps.normal ;

        // if we are in shadow => diffuse and specular are zero
        if ( cosine < 0 || in_shadow ) // cosine < 0 = light source is on the other side of the surface
            return ambient;

        Color diffuse = base_color * comps.object.material.diffuse * cosine ;

        Vector reflectv = Ray::reflect( -lightv , comps.normal );

        float reflect_dot_eye = reflectv * comps.eye ;

        if ( reflect_dot_eye < 0 ) // neglect the specular component
            return ambient + diffuse ;

        Color specular = (light.intensity * comps.object.material.specular) * powf(reflect_dot_eye,comps.object.material.shininess);

        return ambient + diffuse + specular;
    }

    // checks if the Point is in shadow
    bool is_shadowed( const World &world , const Point &point )
    {
        Vector p_to_light = world.getLight().position - point;
        float distance = p_to_light.magnitude() ;

        Ray shadow_ray ( point , p_to_light.normalize() );
        auto list = world.intersect(shadow_ray);

        auto hit = Intersection::get_hit(list);

        // return true if we have a hit and that hit happened closer to the point than the distance to the light source
        return ( hit.has_value() && hit->t < distance ) ;
    }

    Color get_reflected_color(const World &world, const LightComputations &comps, int remaining)
    {
        if ( remaining-- <= 0 || comps.object.material.reflectance == 0 )
        {
            return Color(0,0,0); // object not reflective, return black
        }
        else
        {
            // calculate the reflected ray using the direction included in the LightComputations struct
            // TODO: it would maybe better to not compute reflected inside comps since it may not be used
            // defer its creation until this point where we are sure that we would need it
            Ray reflected_ray(comps.over_point , comps.reflected );

//#ifndef NDEBUG
//            const auto list = world.intersect( reflected_ray );
//            const auto closest = Intersection::get_hit(list) ;
//
//            assert( closest.has_value() && (closest.value().obj != &(comps.object)) ); // test for self intersection
//#endif

            return color_at(world, reflected_ray, true , remaining ) * comps.object.material.reflectance ;
        }
    }

    Color get_refracted_color(const World &world, const LightComputations &comps, int remaining)
    {
        if ( remaining-- <= 0 || comps.object.material.transparency == 0 )
            return Color(0,0,0); // black

        float n_ratio = comps.n1 / comps.n2 ;
        float cos_i = comps.eye * comps.normal ; // both are unit vectors

        // use snell's law
        float sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i ); // trig identity

        if (sin2_t > 1 ) // total internal reflection, not the job of this function
            return Color(0,0,0); // black

        float cos_t = sqrtf(1 - sin2_t) ;
        Vector direction =  comps.normal * ( n_ratio * cos_i - cos_t ) -comps.eye * n_ratio ;

        // create the refracted ray
        Ray refracted ( comps.under_point , direction );

        return color_at( world , refracted , true , remaining );
    }

    float get_schlick_factor(const LightComputations &comps)
    {
        // find the cosine between the angle between the eye and normal vectors
        float cos = comps.eye * comps.normal ;

        //total internal reflection can only occur when n1 > n2
        if ( comps.n1 > comps.n2 ) // check for internal reflection
        {
            float n = comps.n1 / comps.n2;
            float sin2_t =  n*n * ( 1 - cos*cos ) ;
            if (  sin2_t > 1 )
                return 1; // 1 = all reflections not refractions
            cos = sqrtf( 1 - sin2_t ); // use this instead of previous value
        }

        // use schlick's formula
        float r0 = (comps.n1 - comps.n2) / ( comps.n1 + comps.n2 )  ;
        r0 *= r0;
        return r0 + ( 1 - r0 ) * powf( 1 - cos , 5 );
    }
}