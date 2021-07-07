#include "Plane.h"
#include <cmath>
#include "Ray.h"
#include "Intersection.h"
#include "Vec4.h"

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

Vector Plane::local_normal_at(const Point &point) const
{
    return Vec4::getVector(0,1,0); // local plane is always in the XZ plane
}
