#include "Sphere.h"
#include "Intersection.h"
#include "Ray.h"
#include "Bounds3f.h"

bool Sphere::local_intersect(const Ray &local_ray, Intersection &record) const
{
    bool hit = false;
    Vec3f sphere_to_ray(local_ray.origin); // same as subtracting from the origin

    float a = local_ray.direction * local_ray.direction;
    float b = 2 * ( local_ray.direction * sphere_to_ray );
    float c = sphere_to_ray * sphere_to_ray - 1;

    float delta = b*b - 4*a*c;

    if ( delta >= 0 )
    {
        const auto inter1 = (-b - sqrtf(delta)) / (2*a);
        const auto inter2 = (-b + sqrtf(delta)) / (2*a);

        // TODO: do we need to check both cases ?
        if ( inter1 > 0 && inter1 < local_ray.tMax )
        {
            local_ray.tMax = inter1;
            record.obj = this;
            hit = true;
        }
        else if ( inter2 > 0 && inter2 < local_ray.tMax )
        {
            local_ray.tMax = inter2;
            record.obj = this;
            hit = true;
        }
    }

    return hit;
}

Vec3f Sphere::local_normal_at(const Point3f &local_point) const
{
    // locally, calculating the normal is as easy as subtracting the origin(0,0,0) from the surface point
    return Vec3f(local_point);
}

Bounds3f Sphere::objectBounds() const
{
    // out sphere in object space is always centered at 0 with radius = 1
    return Bounds3f( Point3f(-1,-1,-1) , Point3f(1,1,1)  );
}
