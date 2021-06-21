#include "tracing.h"

namespace Lighting
{
    Color color_at(const World &world, const Ray &ray)
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

        // check if the intersection we got was is on the outside or on the inside
        if ( normal * eye < 0 ) // cosine is negative, intersection happened on the inside
            normal = -normal;

        return lighting( first_inter->obj->material , world.getLight() , surface_point , eye , normal );
    }

    Color lighting ( const Material &material , const Light &light , const Point &point , const Vector &eye , const Vector &normal )
    {
        Color base_color = material.color * light.intensity; // base color made up of the light color and material color

        // calculate lightv as vector vector from point to the light source
        Vector lightv = light.position - point ;
        lightv.normalize();

        Color ambient = base_color * material.ambient ;

        // lightv and normal are both normalized vectors
        float cosine = lightv * normal ;

        if ( cosine < 0 ) // light source is on the other side of the surface
            return ambient;

        Color diffuse = base_color * material.diffuse * cosine ;

        Vector reflectv = Ray::reflect( -lightv , normal );
        float reflect_dot_eye = reflectv * eye ;

        if ( reflect_dot_eye < 0 ) // neglect the specular component
            return ambient + diffuse ;

        Color specular = light.intensity * material.specular * powf(reflect_dot_eye,material.shininess);

        return ambient + diffuse + specular;
    }
}