#include "Vec3f.h"
#include "Point3f.h"

Vec3f::Vec3f(const Point3f &point) : x(point.x) , y(point.y) , z(point.z) {}

Vec3f& Vec3f::operator=(const Point3f &point)
{
    // TODO: recheck this, is this correct ?
    x = point.x;
    y = point.y;
    z = point.z;

    return *this;
}