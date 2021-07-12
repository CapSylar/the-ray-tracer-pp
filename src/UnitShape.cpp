#include "UnitShape.h"
#include "Intersection.h"
#include "Ray.h"

void UnitShape::intersect(const Ray &ray, std::vector<Intersection> &list) const
{
    Ray copy_ray = ray;
    copy_ray.transform(inverse_trans);

    local_intersect( copy_ray , list );
}

Vec3f UnitShape::normal_at(const Point3f &surface_point) const
{
    // first inverse_trans surface point from world space to object space
    Point3f local_point = inverse_trans * surface_point;
    // calculate the normal in object space
    auto local_normal = local_normal_at( local_point );

    // convert the normal back to the world system
    //TODO: consider skipping the computing the inverse of the transpose and just using normal trans matrix, since
    // most of the time we are just using uniform scaling for the scene primitives

    Vec3f world_normal = inverse_trans.transpose_copy() * local_normal ;

    return world_normal.normalize() ;
}