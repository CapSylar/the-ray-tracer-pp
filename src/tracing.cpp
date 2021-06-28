#include "tracing.h"
#include "utilities.h"
#include "LightComputations.h"
#include "Color.h"
#include "World.h"

namespace Lighting
{
    Color color_at(const World &world, const Ray &ray, bool calc_shadow, int remaining)
    {
        // get intersection list by intersection the ray in the world
        auto list = world.intersect(ray);

        // get the first intersection
        auto first_inter = Intersection::get_hit(list);

        if (!first_inter.has_value()) // if no intersection return black
            return Color(0, 0, 0);

        // compute the necessary values for Phong shading
        LightComputations comps ( first_inter.value() , ray );

        bool in_shadow = false;
        if ( calc_shadow )
            in_shadow = Lighting::is_shadowed( world , comps.adjusted );

        Color surface_color = get_surface_color( world.getLight() , comps , in_shadow);
        Color reflected_color = get_reflected_color(world, comps, remaining );

        return surface_color + reflected_color;
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

//        std::cout << "reflectv" << reflectv.magnitude() << "comps.eye" << comps.eye.magnitude() << '\n' ;

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
            Ray reflected_ray( comps.adjusted , comps.reflected );
            return color_at(world, reflected_ray, false, remaining ) * comps.object.material.reflectance ;
        }
    }
}