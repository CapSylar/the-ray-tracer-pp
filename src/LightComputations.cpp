#include "LightComputations.h"

#include "Ray.h"
#include "Intersection.h"
#include "UnitShape.h"
#include "utilities.h"
#include <algorithm>
#include <vector>

LightComputations::LightComputations(const Intersection &inter, const Ray &ray) :
        object(*inter.obj) , surface_point( ray.position(ray.tMax)) ,
        normal( inter.obj->normal_at( (inter._u > 0 || inter._v > 0) ? (Point3f(inter._u , inter._v , 0)) : (surface_point))) ,
        eye(-ray.direction.normalize_copy())
{
    // adjust the surface_point slightly to avoid "acne" , aka where an object shadows itself due to imprecision of floating point numbers
    // search for ray tracing acne

    // check if the intersection we got was is on the outside or on the inside
    if (normal * eye < 0) // cosine is negative, intersection happened on the inside
    {
        normal = -normal;
        // only support for isolated materials in space, so if the intersection happened on the inside of a transparent material, thus the ray is leaving
        n1 = inter.obj->getMaterial()->refractive_index;
        n2 = 1;
    }
    else
    {
        // intersection happened on the outside, then we are entering a transparent material
        n1 = 1;
        n2 = inter.obj->getMaterial()->refractive_index;
    }

    over_point = surface_point + normal * eps ;
    under_point = surface_point - normal * eps ;
    reflected = Ray::reflect(ray.direction, normal);
}
