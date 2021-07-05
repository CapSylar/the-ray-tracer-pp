#ifndef RAY_TRACER_LIGHTCOMPUTATIONS_H
#define RAY_TRACER_LIGHTCOMPUTATIONS_H

#include "Vec4.h"
#include "Intersection.h"

class Intersection;
class Ray;

// a data structure used to stored all the calculated vectors and points that can be used to calculate the color at that point
struct LightComputations
{
    LightComputations( const Intersection& inter , const Ray &ray ) ;
    LightComputations( const Intersection& inter , const Ray &ray , const std::vector<Intersection> &list );
    LightComputations ( const Shape &Object , Vector position , Vector Normal , Vector Eye ) : object(Object) ,
            surface_point(position) , normal(Normal) , eye(Eye) , n1(1) , n2(1)  {}

    const Shape &object;
    Point surface_point;
    Vector normal; // normal of the surface pointing away from the surface
    Vector eye; // inverse of the incident ray direction
    Point over_point; // a point situated ~ surface_point but moved slightly so that it is over the surface
    Point under_point; // a point situated ~ surface_point but moved slightly so that it is underneath the surface
    Vector reflected;

    // for refraction
    float n1, n2;
};


#endif //RAY_TRACER_LIGHTCOMPUTATIONS_H
