#include "Triangle.h"
#include "Ray.h"
#include "Intersection.h"

void Triangle::local_intersect(const Ray &ray, std::vector<Intersection> &list) const
{
    // `Moeller-Trumbore` ray triangle intersection algorithm
    // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection

    // calculate the determinant => scalar triple product (D cross E2) dot E1
    const auto dir_cross_e2 = Vec4::cross(ray.direction , e2 );
    const auto determinant = e1 * dir_cross_e2;

    if ( std::abs(determinant) < eps )
        return;

    const auto inv = 1 / determinant; // precompute the inverse needed by cramer's rule

    // calculate the u coordinate of the triangle intersection
    const auto p1_to_origin = ray.origin - _p1 ;
    const auto u = inv * (p1_to_origin * dir_cross_e2); // cramer

    // if u < 0 or u > 1 then the point is outside the triangle, no intersection

    if ( u < 0 || u > 1 )
        return;

    // calculate the v coordinate of the triangle intersection
    const auto origin_cross_e1 = Vec4::cross( p1_to_origin , e1 );
    const auto v = inv * ( ray.direction * origin_cross_e1 ); // cramer

    // if v < 0 or v > 1 then the point is outside the triangle, no intersection

    if ( v < 0 || (u+v) > 1 )
        return;

    // calculate t by solving for the final unknown using cramer
    const auto t = inv * ( e2 * origin_cross_e1 );
    list.emplace_back( t , this );
}

Vector Triangle::local_normal_at(const Point &point) const
{
    return normal;
}
