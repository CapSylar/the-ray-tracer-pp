#include "Cylinder.h"
#include "Ray.h"
#include <vector>
#include "utilities.h"
#include "Intersection.h"
#include "Bounds3f.h"

bool Cylinder::local_intersect(const Ray &ray, Intersection &record) const
{
    bool hit = false;
    const auto a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z ;

    if (!isEqualF(a, 0))
    {
        const auto b = 2 * ray.direction.x * ray.origin.x + 2 * ray.direction.z * ray.origin.z ;
        const auto c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;

        const auto disc = b*b - 4*a*c;

        if ( disc >= 0 )
        {
            const auto t0 = (-b-std::sqrt(disc))/(2*a) ;
            const auto t1 = (-b+std::sqrt(disc))/(2*a) ;

            // calculate the point of intersection by using rays, if a point is between the caps then the intersection is valid

            const auto y0 = ray.origin.y + t0 * ray.direction.y ;
            const auto y1 = ray.origin.y + t1 * ray.direction.y ;

            if (y0 > zMin && y0 < zMax )
            {
                if ( t0 < ray.tMax )
                {
                    ray.tMax = t0;
                    record.obj = this;
                    hit = true;
                }
            }

            if (y1 > zMin && y1 < zMax )
            {
                if ( t1 < ray.tMax )
                {
                    ray.tMax = t1;
                    record.obj = this;
                    hit = true;
                }
            }
        }
    }

    if ( is_capped && intersect_caps(ray , record ) ) // also check intersection with caps
        hit = true;

    return hit;
}

Vec3f Cylinder::local_normal_at(const Point3f &point) const
{
    const auto dist = point.x * point.x + point.z*point.z ;

    if ( dist < 1 ) // possible to have intersection on caps
    {
        // check intersection at upper cap
        if (point.y >= zMax - eps )
            return Vec3f( 0, 1 , 0); // upwards in +y

        // check intersection at lower cap
        if (point.y <= zMin + eps )
            return Vec3f( 0 , -1, 0 ); // downwards in -y
    }

    // intersection not on caps
    return Vec3f( point.x , 0 , point.z );
}

inline
bool Cylinder::check_cap(const Ray &ray, float t)
{
    const auto x = ray.origin.x + ray.direction.x * t;
    const auto z = ray.origin.z + ray.direction.z * t;

    return ( (x*x + z*z) <= 1 ); // check if inside the cap
}

bool Cylinder::intersect_caps(const Ray &ray, Intersection &record) const
{
    bool hit = false;
    // check if ray is moving on y, if not it couldn't intersect with the caps
    if (!isEqualF(ray.direction.y, 0) )
    {

        // check intersection at the lower cap
        const auto t_lower = (zMin - ray.origin.y ) / ray.direction.y ;

        if (check_cap( ray , t_lower ))
        {
            if ( t_lower < ray.tMax )
            {
                ray.tMax = t_lower;
                record.obj = this;
                hit = true;
            }

        }

        const auto t_upper = (zMax - ray.origin.y ) / ray.direction.y ;

        if (check_cap( ray , t_upper ))
        {
            if ( t_upper < ray.tMax )
            {
                ray.tMax = t_upper;
                record.obj = this;
                hit = true;
            }
        }
    }

    return hit;
}

Bounds3f Cylinder::objectBounds() const
{
    // cylinder in object space has radius 1 and extends from zMin to zMax
    return Bounds3f( Point3f(-1,-1,zMin) , Point3f(1,1,zMax) );
}
