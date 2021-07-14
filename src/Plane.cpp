#include "Plane.h"
#include <cmath>
#include "Ray.h"
#include "Intersection.h"
#include "Vec3f.h"
#include "Bounds3f.h"

void Plane::local_intersect(const Ray &ray, std::vector<Intersection> &list) const
{
    if (fabsf(ray.direction.y) < eps ) // if parallel to the plane
    {
        return;
    }
    else
    {
        list.emplace_back( -ray.origin.y / ray.direction.y , this );
    }
}

Vec3f Plane::local_normal_at(const Point3f &point) const
{
    return Vec3f(0,1,0); // local plane is always in the XZ plane
}

Bounds3f Plane::objectBounds() const
{
    //TODO: should an infinite plane have a bounding box? how will it bound the plane :) ?
    return Bounds3f();
}
