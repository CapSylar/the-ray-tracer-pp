#include "Sphere.h"
#include "Intersection.h"

std::vector<Intersection> Sphere::intersect(const Ray &ray)
{
    std::vector<Intersection> inters;
    intersect(ray, inters);
    return inters;
}

void Sphere::intersect(const Ray &ray, std::vector<Intersection> &list)
{
    Ray copy_ray = ray;
    copy_ray.transform(transform.invert_copy()); // TODO: inversion at every intersection test, no no no!!
    Vector sphere_to_ray = copy_ray.origin - Vec4::getPoint(0,0,0); // TODO: fix this ugliness

    float a = copy_ray.direction * copy_ray.direction;
    float b = 2 * ( copy_ray.direction * sphere_to_ray );
    float c = sphere_to_ray * sphere_to_ray - 1;

    float delta = b*b - 4*a*c;

    if ( delta >= 0 ) // we have 1+ intersection(s)
    {
        list.emplace_back( ((-b - sqrtf(delta)) / (2*a)) , *this );
        list.emplace_back( ((-b + sqrtf(delta)) / (2*a)) , *this );
    }
}