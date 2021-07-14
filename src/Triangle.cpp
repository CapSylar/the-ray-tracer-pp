#include "Triangle.h"
#include "Ray.h"
#include "Intersection.h"
#include "Bounds3f.h"

void Triangle::intersect(const Ray &ray, std::vector<Intersection> &list) const
{
    // `Moeller-Trumbore` ray triangle intersection algorithm
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection

    // calculate the determinant => scalar triple product (D cross E2) dot E1
    const auto dir_cross_e2 = cross(ray.direction , e2 );
    const auto determinant = e1 * dir_cross_e2;

    if ( std::abs(determinant) < eps )
        return;

    const auto inv = 1 / determinant; // precompute the inverse needed by cramer's rule

    // calculate the u coordinate of the triangle intersection
    const Vec3f p1_to_origin = ray.origin - _p1 ;
    const auto u = inv * (p1_to_origin * dir_cross_e2); // cramer

    // if u < 0 or u > 1 then the point is outside the triangle, no intersection

    if ( u < 0 || u > 1 )
        return;

    // calculate the v coordinate of the triangle intersection
    const auto origin_cross_e1 = cross( p1_to_origin , e1 );
    const auto v = inv * ( ray.direction * origin_cross_e1 ); // cramer

    // if v < 0 or v > 1 then the point is outside the triangle, no intersection

    if ( v < 0 || (u+v) > 1 )
        return;

    // calculate t by solving for the final unknown using cramer
    const auto t = inv * ( e2 * origin_cross_e1 );
    list.emplace_back( t , this , u , v );
}

Vec3f Triangle::normal_at(const Point3f &point) const
{
    //TODO: we are passing u and v in the point, find a cleaner way to do this while staying consistent with API

    // if triangle is smooth then we can use normal interpolation, else just use _n1 which is uniform across the whole triangle
    if ( isSmooth )
    {
        // return interpolation using u and v encoded in point x and y respectively
        return _n2 * point.x + _n3 * point.y + _n1 * ( 1 - point.x - point.y );
    }
    else
    {
        return _n1 ;
    }
}

Bounds3f Triangle::worldBounds() const
{
    return Bounds3f();
}
