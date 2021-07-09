#ifndef RAY_TRACER_PLANE_H
#define RAY_TRACER_PLANE_H

#include "UnitShape.h"

class Plane : public UnitShape
{
public:
    explicit Plane (  Material *mat  , Mat4 trans = Mat4() ) : UnitShape( trans , mat ) {}
    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    [[nodiscard]] Vector local_normal_at(const Point &point) const override;
};


#endif //RAY_TRACER_PLANE_H
