#include "Plane.h"
#include <cmath>
#include "Ray.h"
#include "Intersection.h"
#include "Vec3f.h"
#include "Bounds3f.h"

bool Plane::local_intersect(const Ray &ray, Intersection &record) const
{
    bool hit = false;

    if (fabsf(ray.direction.y) >= eps) // if not parallel to the plane
    {
        const auto t = -ray.origin.y / ray.direction.y;

        if ( t > 0 && t < ray.tMax )
        {
            ray.tMax = t;
            record = Intersection( t , this );
            hit = true;
        }
    }

    return hit;
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
