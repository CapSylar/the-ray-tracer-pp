#include "Cube.h"
#include "Ray.h"
#include <algorithm>
#include "Intersection.h"

void Cube::local_intersect(const Ray &ray, std::vector<Intersection> &list) const
{
    // TODO: optimize intersection testing

    const auto x_pair = get_axis_intersections( ray.origin.x , ray.direction.x );
    const auto y_pair = get_axis_intersections( ray.origin.y , ray.direction.y );
    const auto z_pair = get_axis_intersections( ray.origin.z , ray.direction.z );

    float tmin = std::max( std::max(x_pair.first , y_pair.first), z_pair.first ) ;
    float tmax = std::min( std::min(x_pair.second , y_pair.second) , z_pair.second ) ;

    if ( tmin > tmax ) // no intersection
        return;

    list.emplace_back( tmin , *this );
    list.emplace_back( tmax , *this );
}

Vector Cube::local_normal_at(const Point &point) const
{
    float max = std::max ( point.x , std::max( point.y , point.z ));

    if ( max == std::abs(point.x) ) // we are on one of the two surfaces that lie in YZ
    {
        return Vec4::getVector( point.x , 0 , 0 );
    }
    else if ( max == std::abs(point.y) ) // we are on one of the two surface that lie in XZ
    {
        return Vec4::getVector( 0 , point.y , 0 );
    }
    else
    {
        return Vec4::getVector( 0 , 0 , point.z );
    }
}

std::pair<float,float> Cube::get_axis_intersections( float origin , float direction )
{
    std::pair<float,float> t_pair;
    float axis1 = (-1-origin);
    float axis2 = (1 - origin );
    if ( std::fabs(direction) >= eps ) // we have a intersection with the two axis
    {
        t_pair = { axis1 / direction  , axis2 / direction  };
    }
    else
    {
        t_pair = { axis1 * INFINITY,  axis2 * INFINITY };  // no intersection
    }

    if ( t_pair.first > t_pair.second )
        t_pair = { t_pair.second , t_pair.first }; // reorder them => ( min , max );

    return t_pair;
}