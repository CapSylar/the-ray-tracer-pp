#include "Cube.h"
#include "Ray.h"
#include <algorithm>
#include "Intersection.h"
#include "Bounds3f.h"

bool Cube::local_intersect(const Ray &ray, Intersection &record) const
{
    bool hit = false;
    // TODO: optimize intersection testing

    const auto x_pair = get_axis_intersections( ray.origin.x , ray.direction.x );
    const auto y_pair = get_axis_intersections( ray.origin.y , ray.direction.y );
    const auto z_pair = get_axis_intersections( ray.origin.z , ray.direction.z );

    const float tmin = std::max( std::max(x_pair.first , y_pair.first), z_pair.first ) ;
    const float tmax = std::min( std::min(x_pair.second , y_pair.second) , z_pair.second ) ;

    if ( tmin <= tmax && tmin < ray.tMax ) // if tmin > tmax => no intersection
    {
        ray.tMax = tmin;
        record.obj = this;
        hit = true;
    }

    return hit;
}

Vec3f Cube::local_normal_at(const Point3f &point) const
{
    const float abs_x = std::abs(point.x);
    const float abs_y = std::abs(point.y);
    const float abs_z = std::abs(point.z);


    const float max = std::max ( abs_x , std::max( abs_y , abs_z ));

    if ( max == abs_x ) // we are on one of the two surfaces that lie in YZ
    {
        return Vec3f( point.x , 0 , 0 ).normalize();
    }
    else if ( max == abs_y ) // we are on one of the two surface that lie in XZ
    {
        return Vec3f( 0 , point.y , 0 ).normalize();
    }
    else
    {
        return Vec3f( 0 , 0 , point.z ).normalize();
    }
}

std::pair<float,float> Cube::get_axis_intersections( float origin , float direction )
{
    std::pair<float,float> t_pair;
    const float axis1 = (-1-origin);
    const float axis2 = (1-origin);
    if ( std::fabs(direction) >= eps ) // we have a intersection with the two axis
    {
        t_pair = { axis1 / direction  , axis2 / direction  };
    }
    else
    {
        t_pair = { axis1 * INFINITY,  axis2 * INFINITY };  // no intersection
    }

    if ( t_pair.first > t_pair.second )
        t_pair = { t_pair.second , t_pair.first }; // reorder them => ( zMin , zMax );

    return t_pair;
}

Bounds3f Cube::objectBounds() const
{
    // cube in object space is always centered with extending from -1 to 1 at every axis

    return Bounds3f( Point3f(-1,-1,-1) , Point3f(1,1,1) );

}
