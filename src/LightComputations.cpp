#include "LightComputations.h"

#include "Ray.h"
#include "Intersection.h"
#include "Shape.h"
#include "utilities.h"
#include <algorithm>

LightComputations::LightComputations(const Intersection &inter, const Ray &ray) :
        object(*inter.obj) , surface_point( ray.position(inter.t)) , normal( inter.obj->normal_at(surface_point)) , eye(-ray.direction.normalize_copy()) ,
        over_point(surface_point + normal * eps * 5 ) , under_point(surface_point - normal * eps * 1000000 ) ,reflected(Ray::reflect(ray.direction , normal ) ) , n1(1) , n2(1)
{
    // adjust the surface_point slightly to avoid "acne" , aka where an object shadows itself due to imprecision of floating point numbers
    // search for ray tracing acne

     // compute the necessary values later used for Phong shading
    // check if the intersection we got was is on the outside or on the inside
    if ( normal * eye < 0 ) // cosine is negative, intersection happened on the inside
        normal = -normal;
}

LightComputations::LightComputations(const Intersection &inter, const Ray &ray, const std::vector<Intersection> &list) :
        LightComputations( inter , ray )
{
    // calculate n1 and n2 used for refraction
    // the ray tracer allows to embed material of different refractive properties inside each other
    // simple ray tracer that only allow transparent object to exist in isolation in the scene do not need what is below

    std::vector<const Shape *> shapes;

    for ( const auto &intersection : list )
    {
        bool hit = false;
        // find n1
        if ( intersection == inter ) // if intersection is the hit
        {
            hit = true;
            n1 = shapes.empty() ? 1 : shapes.back()->material.refractive_index ;
        }

        // if we already included the shape inside the list, then the hit means that we are exiting the material,
        // else it means we are entering it

        const auto current =  std::find( shapes.begin() , shapes.end() , intersection.obj ) ;
        if ( current != shapes.end() ) // if in the list
        {
            shapes.erase( current );
        }
        else // else insert in the list
        {
            shapes.push_back(intersection.obj );
        }

        // find n2
        if ( hit )
        {
            n2 = shapes.empty() ? 1 : shapes.back()->material.refractive_index ;
        }

    }

}
