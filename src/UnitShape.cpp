#include "UnitShape.h"
#include "Intersection.h"
#include "Ray.h"

void UnitShape::intersect(const Ray &ray, std::vector<Intersection> &list) const
{
    Ray copy_ray = ray;
    copy_ray.transform(inverse_trans);

    local_intersect( copy_ray , list );
}

Vector UnitShape::normal_at(const Point &surface_point) const
{
    // first inverse_trans surface point from world space to object space
    Vector local_point = inverse_trans * surface_point;
    // calculate the normal in object space
    auto local_normal = local_normal_at( local_point );

    // convert the normal back to the world system
    Vector world_normal = inverse_trans.transpose_copy() * local_normal ;
    world_normal.w = 0;

    return world_normal.normalize() ;
}