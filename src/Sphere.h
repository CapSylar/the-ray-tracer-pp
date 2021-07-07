#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include <vector>
#include <optional>

#include "Shape.h"
class Ray;
class Intersection;

class Sphere : public Shape
{
public:
    explicit Sphere( Material *mat , Mat4 trans = Mat4() ) : Shape( trans , mat ) {}

private:
    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    Vector local_normal_at(const Point &point) const override;
};


#endif //RAY_TRACER_SPHERE_H
