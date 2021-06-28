#include "Sphere.h"
#include "Intersection.h"

void Sphere::local_intersect(const Ray &local_ray, std::vector<Intersection> &list) const
{
    Vector sphere_to_ray = local_ray.origin - Vec4::getPoint(0,0,0); // TODO: fix this ugliness

    float a = local_ray.direction * local_ray.direction;
    float b = 2 * ( local_ray.direction * sphere_to_ray );
    float c = sphere_to_ray * sphere_to_ray - 1;

    float delta = b*b - 4*a*c;

    if ( delta >= 0 ) // we have 1+ intersection(s)
    {
        list.emplace_back( ((-b - sqrtf(delta)) / (2*a)) , *this );
        list.emplace_back( ((-b + sqrtf(delta)) / (2*a)) , *this );
    }
}

Vector Sphere::local_normal_at(const Point &local_point) const
{
    // locally, calculating the normal is as easy as subtracting the origin(0,0,0) from the surface point
    return local_point - Vec4::getPoint();
}