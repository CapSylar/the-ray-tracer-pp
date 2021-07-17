#include "Lighting.h"
#include "utilities.h"
#include "LightComputations.h"
#include "World.h"

#include <cassert>

namespace Lighting
{
    Color3f color_at(const World &world, const Ray &ray, bool calc_shadow, int remaining)
    {
        // get intersection list by intersection the ray in the world
        Intersection record;
        bool hit = world.intersect(ray , record );

        // get the first intersection
//        const auto first_inter = Intersection::get_hit(list);

        if (!hit) // if no intersection return black
            return Color3f(0, 0, 0);

        // compute the necessary values for Phong shading
        LightComputations comps ( record , ray );

        return shade_hit( world , comps , calc_shadow , remaining );
    }

    Color3f shade_hit ( const World &world , const LightComputations &comps , bool calc_shadow , int remaining )
    {
        bool in_shadow = false;
        if ( calc_shadow )
            in_shadow = Lighting::is_shadowed( world , comps.over_point );

        Color3f surface_color = get_surface_color( world.getLight() , comps , in_shadow);
        Color3f reflected_color = get_reflected_color(world, comps, remaining );
        Color3f refracted_color = get_refracted_color( world , comps , remaining );

        const auto &mat = comps.object.getMaterial() ;
        if ( mat->reflectance > 0 && mat->transparency > 0 ) // use Schlick's approx in this case
        {
            const auto factor = get_schlick_factor( comps );
            return surface_color +  (reflected_color * factor) + (refracted_color * ( 1 - factor )) ;
        }
        else
        {
            return surface_color + reflected_color + refracted_color ;
        }
    }

    Color3f get_surface_color ( const Light &light , const LightComputations &comps , bool in_shadow )
    {
        Color3f base_color = comps.object.getMaterial()->get_albedo(comps.surface_point) * light.intensity; // base color made up of the light color and material color

        // calculate lightv as vector from point to the light source
        auto lightv = light.position - comps.surface_point ;
        lightv.normalize();

        Color3f ambient = base_color * comps.object.getMaterial()->ambient ;

        // lightv and normal are both normalized vectors
        const auto cosine = lightv * comps.normal ;

        // if we are in shadow => diffuse and specular are zero
        if ( cosine < 0 || in_shadow ) // cosine < 0 = light source is on the other side of the surface
            return ambient;

        Color3f diffuse = base_color * comps.object.getMaterial()->diffuse * cosine ;

        Vec3f reflectv = Ray::reflect( -lightv , comps.normal );

        float reflect_dot_eye = reflectv * comps.eye ;

        if ( reflect_dot_eye < 0 ) // neglect the specular component
            return ambient + diffuse ;

        Color3f specular = (light.intensity * comps.object.getMaterial()->specular) * powf(reflect_dot_eye,comps.object.getMaterial()->shininess);

        return ambient + diffuse + specular;
    }

    // checks if the Point is in shadow
    bool is_shadowed( const World &world , const Point3f &point )
    {
        auto p_to_light = world.getLight().position - point;
        float distance = p_to_light.length() ;

        Ray shadow_ray ( point , p_to_light.normalize() , distance ); // tMax = distance

        Intersection record;
        bool hit = world.intersectP(shadow_ray , record );

        // return true if we have a hit and that hit happened closer to the point than the distance to the light source
        return hit ;
    }

    Color3f get_reflected_color(const World &world, const LightComputations &comps, int remaining)
    {
        if ( remaining-- <= 0 || comps.object.getMaterial()->reflectance == 0 )
        {
            return Color3f(0,0,0); // object not reflective, return black
        }
        else
        {
            // calculate the reflected ray using the direction included in the LightComputations struct
            // TODO: it would maybe better to not compute reflected inside comps since it may not be used
            // defer its creation until this point where we are sure that we would need it
            Ray reflected_ray(comps.over_point , comps.reflected );

            return color_at(world, reflected_ray, true , remaining ) * comps.object.getMaterial()->reflectance ;
        }
    }

    Color3f get_refracted_color(const World &world, const LightComputations &comps, int remaining)
    {
        if ( remaining-- <= 0 || comps.object.getMaterial()->transparency == 0 )
            return Color3f(0,0,0); // black

        float n_ratio = comps.n1 / comps.n2 ;
        float cos_i = comps.eye * comps.normal ; // both are unit vectors

        // use snell's law
        float sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i ); // trig identity

        if (sin2_t > 1 ) // total internal reflection, not the job of this function
            return Color3f(0,0,0); // black

        float cos_t = sqrtf(1 - sin2_t) ;
        Vec3f direction =  comps.normal * ( n_ratio * cos_i - cos_t ) -comps.eye * n_ratio ;

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