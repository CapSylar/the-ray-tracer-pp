#ifndef RAY_TRACER_PLANE_H
#define RAY_TRACER_PLANE_H

#include "UnitShape.h"

class Plane : public UnitShape
{
public:
    explicit Plane (  Material *mat  , Mat4 trans = Mat4() ) : UnitShape( trans , mat ) {}
    bool local_intersect(const Ray &ray, Intersection &record) const override;
    [[nodiscard]] Vec3f local_normal_at(const Point3f &point) const override;

    [[nodiscard]] Bounds3f objectBounds() const override;
};


#endif //RAY_TRACER_PLANE_H
