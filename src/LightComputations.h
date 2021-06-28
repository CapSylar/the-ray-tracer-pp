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
    LightComputations ( const Shape &Object , Vector position , Vector Normal , Vector Eye ) : object(Object) ,
            surface_point(position) , normal(Normal) , eye(Eye) {}

    const Shape &object;
    Point surface_point;
    Vector normal;
    Vector eye;
    Point adjusted;
    Vector reflected;
};


#endif //RAY_TRACER_LIGHTCOMPUTATIONS_H
