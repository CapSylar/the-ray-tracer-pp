#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"

void Shape::intersect(const Ray &ray, std::vector<Intersection> &list) const
{
    Ray copy_ray = ray;
    copy_ray.transform(transform.invert_copy()); // TODO: inversion at every intersection test, no no no!!

    local_intersect( copy_ray , list );
}

Vector Shape::normal_at(const Point &surface_point) const
{
    // first transform surface point from world space to object space
    Vector local_point = transform.invert_copy() * surface_point;
    // calculate the normal in object space
    auto local_normal = local_normal_at( local_point );

    // convert the normal back to the world system
    Vector world_normal = transform.invert_copy().transpose() * local_normal ;
    world_normal.w = 0;

    return world_normal.normalize() ;
}