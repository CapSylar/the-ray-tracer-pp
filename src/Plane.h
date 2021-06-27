#ifndef RAY_TRACER_PLANE_H
#define RAY_TRACER_PLANE_H

#include "Shape.h"

class Plane : public Shape
{
public:
    explicit Plane ( Mat4 trans = Mat4() , Material mat = Material() ) : Shape( trans , mat ) {}
    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    Vector local_normal_at(const Point &point) const override;
};


#endif //RAY_TRACER_PLANE_H
