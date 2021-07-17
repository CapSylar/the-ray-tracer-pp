#ifndef RAY_TRACER_LIGHTCOMPUTATIONS_H
#define RAY_TRACER_LIGHTCOMPUTATIONS_H

#include "Intersection.h"
#include "Vec3f.h"
#include "Point3f.h"

class Intersection;
class Ray;

// a data structure used to stored all the calculated vectors and points that can be used to calculate the color at that point
struct LightComputations
{
    LightComputations( const Intersection& inter , const Ray &ray ) ;
//    LightComputations( const Intersection& inter , const Ray &ray , const std::vector<Intersection> &list );
    LightComputations ( const Primitive &Object , Point3f position , Vec3f Normal , Vec3f Eye ) : object(Object) ,
            surface_point(position) , normal(Normal) , eye(Eye) , n1(1) , n2(1)  {}

    const Primitive &object;
    Point3f surface_point;
    Vec3f normal; // normal of the surface pointing away from the surface
    Vec3f eye; // inverse of the incident ray direction
    Point3f over_point; // a point situated ~ surface_point but moved slightly so that it is over the surface
    Point3f under_point; // a point situated ~ surface_point but moved slightly so that it is underneath the surface
    Vec3f reflected;

    // for refraction
    float n1, n2;
};


#endif //RAY_TRACER_LIGHTCOMPUTATIONS_H
