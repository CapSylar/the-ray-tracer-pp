#include "Aggregate.h"

#include "Vec3f.h"
#include <iostream>

//TODO: std::cerr is not the proper way to do it, fix that!!!

const Material *Aggregate::getMaterial() const
{
    std::cerr << "called getMaterial() on aggregate, error" << '\n' ;
    return nullptr;
}

void Aggregate::intersect(const Ray &ray, std::vector<Intersection> &list) const
{
    // do nothing
}

Vec3f Aggregate::normal_at(const Point3f &surface_point) const
{
    std::cerr << "called normal_at() on aggregate, error" << '\n' ;
    return Vec3f();
}
