#include "Cylinder.h"
#include "Ray.h"
#include <vector>
#include "utilities.h"
#include "Intersection.h"

void Cylinder::local_intersect(const Ray &ray, std::vector<Intersection> &list) const
{
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

            if ( y0 > min && y0 < max )
                list.emplace_back( t0 , this );

            if ( y1 > min && y1 < max )
                list.emplace_back( t1 , this );
        }
    }

    if ( is_capped ) // also check intersection with caps
        intersect_caps( ray ,list );
}

Vec3f Cylinder::local_normal_at(const Point3f &point) const
{
    const auto dist = point.x * point.x + point.z*point.z ;

    if ( dist < 1 ) // possible to have intersection on caps
    {
        // check intersection at upper cap
        if ( point.y >= max - eps )
            return Vec3f( 0, 1 , 0); // upwards in +y

        // check intersection at lower cap
        if ( point.y <= min + eps )
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

void Cylinder::intersect_caps(const Ray &ray, std::vector<Intersection> &list) const
{
    // check if ray is moving on y, if not it couldn't intersect with the caps
    if (isEqualF(ray.direction.y, 0) )
        return;

    // check intersection at the lower cap
    const auto t_lower = ( min - ray.origin.y ) / ray.direction.y ;

    if (check_cap( ray , t_lower ))
        list.emplace_back( t_lower , this );

    const auto t_upper = ( max - ray.origin.y ) / ray.direction.y ;

    if (check_cap( ray , t_upper ))
        list.emplace_back( t_upper , this );
}
