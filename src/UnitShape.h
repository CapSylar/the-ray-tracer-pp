#ifndef RAY_TRACER_UNITSHAPE_H
#define RAY_TRACER_UNITSHAPE_H

#include "Material.h"
#include "Mat4.h"
#include "GeometricPrimitive.h"

class Intersection;
class Ray;

// this shape is defined as a unit and then needs and needs to be transformed to the correct position in world space
// by some transform matrix

class UnitShape : public GeometricPrimitive
{
public:
    Mat4 inverse_trans;

    explicit UnitShape ( Mat4 trans , Material* mat ) : GeometricPrimitive(mat) , inverse_trans(trans.invert()) {}

    void intersect(const Ray &ray, std::vector<Intersection> &list) const override ;
    [[nodiscard]] Vec3f normal_at(const Point3f &surface_point) const override ;

    virtual void local_intersect ( const Ray &ray , std::vector<Intersection> &list ) const = 0;
    [[nodiscard]] virtual Vec3f local_normal_at ( const Point3f &point ) const = 0 ;

    [[nodiscard]] Bounds3f worldBounds() const override;
    [[nodiscard]] virtual Bounds3f objectBounds() const = 0;
};


#endif //RAY_TRACER_UNITSHAPE_H
