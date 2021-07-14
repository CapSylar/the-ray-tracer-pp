#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include <vector>
#include <optional>
#include "UnitShape.h"

class Ray;
class Intersection;

class Sphere : public UnitShape
{
public:
    explicit Sphere( Material *mat , Mat4 trans = Mat4() ) : UnitShape( std::move(trans) , mat ) {}

private:
    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    [[nodiscard]] Vec3f local_normal_at(const Point3f &point) const override;

public:
    Bounds3f objectBounds() const override;
};


#endif //RAY_TRACER_SPHERE_H
