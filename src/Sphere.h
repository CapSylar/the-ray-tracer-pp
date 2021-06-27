#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include <vector>
#include <optional>

#include "Ray.h"
//#include "Material.h"
#include "Shape.h"

class Intersection;

class Sphere : public Shape
{
public:
    explicit Sphere( Mat4 trans = Mat4() , Material mat = Material() ) : Shape( trans , mat ) {}

private:
    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    Vector local_normal_at(const Point &point) const override;
};


#endif //RAY_TRACER_SPHERE_H
