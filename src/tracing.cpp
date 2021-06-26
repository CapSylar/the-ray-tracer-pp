#include "tracing.h"
#include "utilities.h"

namespace Lighting
{

    Color color_at(const World &world, const Ray &ray , bool calc_shadow )
    {
        // get intersection list by intersection the ray in the world
        auto list = world.intersect(ray);
        // get the first intersection
        auto first_inter = Intersection::get_hit(list);

        if (!first_inter.has_value()) // if no intersection return black
            return Color(0, 0, 0);

        // compute the necessary values for Phong shading

        Point surface_point = ray.position(first_inter->t);
        Vector normal = first_inter->obj->normal_at(surface_point);
        Vector eye = -ray.direction;

        // adjust the surface_point slightly to avoid "acne" , aka where an object shadows itself due to imprecision of floating point numbers
        // search for ray tracing acne

        surface_point = surface_point + normal * eps * 5 ;

        // check if the intersection we got was is on the outside or on the inside
        if ( normal * eye < 0 ) // cosine is negative, intersection happened on the inside
            normal = -normal;

        bool in_shadow = false;
        if ( calc_shadow )
            in_shadow = Lighting::is_shadowed( world , surface_point );

        return lighting( first_inter->obj->material , world.getLight() , surface_point , eye , normal , in_shadow );
    }


    Color lighting ( const Material &material , const Light &light , const Point &point , const Vector &eye , const Vector &normal , bool in_shadow )
    {
        Color base_color = material.color * light.intensity; // base color made up of the light color and material color

        // calculate lightv as vector vector from point to the light source
        Vector lightv = light.position - point ;
        lightv.normalize();

        Color ambient = base_color * material.ambient ;

        // lightv and normal are both normalized vectors
        float cosine = lightv * normal ;

        // if we are in shadow => diffuse and specular are zero
        if ( cosine < 0 || in_shadow ) // cosine < 0 = light source is on the other side of the surface
            return ambient;

        Color diffuse = base_color * material.diffuse * cosine ;

        Vector reflectv = Ray::reflect( -lightv , normal );
        float reflect_dot_eye = reflectv * eye ;

        if ( reflect_dot_eye < 0 ) // neglect the specular component
            return ambient + diffuse ;

        Color specular = light.intensity * material.specular * powf(reflect_dot_eye,material.shininess);

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
}