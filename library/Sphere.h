#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include <iostream>
#include <vector>
#include <optional>

#include "Ray.h"
#include "Material.h"

class Intersection;

struct Sphere
{
    Sphere( Material mat = Material() , Mat4 trans = Mat4() ) : material(mat) , transform(trans) {}  

    std::vector<Intersection> intersect ( const Ray &ray );
    void intersect ( const Ray &ray , std::vector<Intersection>& list ) ;
    Vector normal_at ( Point world_point ) const ;

    Material material;
    Mat4 transform;
};


#endif //RAY_TRACER_SPHERE_H
