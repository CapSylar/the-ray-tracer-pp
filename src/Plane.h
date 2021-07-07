#ifndef RAY_TRACER_PLANE_H
#define RAY_TRACER_PLANE_H

#include "Shape.h"

class Plane : public Shape
{
public:
    explicit Plane (  Material *mat  , Mat4 trans = Mat4() ) : Shape( trans , mat ) {}
    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    [[nodiscard]] Vector local_normal_at(const Point &point) const override;
};


#endif //RAY_TRACER_PLANE_H
