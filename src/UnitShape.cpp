#include "UnitShape.h"
#include "Intersection.h"
#include "Ray.h"
#include "Bounds3f.h"

bool UnitShape::intersect(const Ray &ray, Intersection &record) const
{
    Ray copy_ray = ray;
    copy_ray.transform(worldToObject);

    bool intersect = local_intersect(copy_ray , record );
    ray.tMax = copy_ray.tMax; // TODO: find cleaner way to handle this, maybe remove tMax from ray altogether

    return intersect;
}

Vec3f UnitShape::normal_at(const Point3f &surface_point) const
{
    // first worldToObject surface point from world space to object space
    Point3f local_point = worldToObject * surface_point;
    // calculate the normal in object space
    auto local_normal = local_normal_at( local_point );

    // convert the normal back to the world system
    //TODO: consider skipping the computing the inverse of the transpose and just using normal trans matrix, since
    // most of the time we are just using uniform scaling for the scene primitives

    return worldToObject.multiplyNormal( local_normal );
}

Bounds3f UnitShape::worldBounds() const
{
    // call the shapes localBounds and transform that to world space
    //TODO: move this code somewhere else, good enough for now
    const Bounds3f bounds = objectBounds();
    // transform both points and reconstruct a bounding box since transforming an AABB may change its alignment

    const Point3f npMin = objectToWorld * bounds.pMin;
    const Point3f npMax = objectToWorld * bounds.pMax;

    return Bounds3f( npMin , npMax );
}
