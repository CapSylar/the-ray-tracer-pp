#include "LightComputations.h"

#include "Ray.h"
#include "Intersection.h"
#include "Shape.h"
#include "utilities.h"

LightComputations::LightComputations(const Intersection &inter, const Ray &ray) :
        object(*inter.obj) , surface_point( ray.position(inter.t)) , normal( inter.obj->normal_at(surface_point)) , eye(-ray.direction.normalize_copy()) ,
        adjusted(surface_point + normal * eps * 5 ) , reflected( Ray::reflect( ray.direction , normal ) )
{
    // adjust the surface_point slightly to avoid "acne" , aka where an object shadows itself due to imprecision of floating point numbers
    // search for ray tracing acne

     // compute the necessary values later used for Phong shading
    // check if the intersection we got was is on the outside or on the inside
    if ( normal * eye < 0 ) // cosine is negative, intersection happened on the inside
        normal = -normal;
}
