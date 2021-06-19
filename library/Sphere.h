#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include <iostream>
#include <vector>
#include <optional>

#include "../src/Ray.h"

class Intersection;

struct Sphere
{
    std::vector<Intersection> intersect ( const Ray &ray );
    void intersect ( const Ray &ray , std::vector<Intersection>& list ) ;

    Mat4 transform;
};


#endif //RAY_TRACER_SPHERE_H
