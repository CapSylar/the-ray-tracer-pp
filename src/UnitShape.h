#ifndef RAY_TRACER_UNITSHAPE_H
#define RAY_TRACER_UNITSHAPE_H

#include "Material.h"
#include "Mat4.h"
#include "GeometricPrimitive.h"

class Intersection;
class Ray;

// this shape is defined as a unit object (for ex. unit sphere at origin (0,0,0)) and then needs and needs to be transformed to the correct position in world space
// by some transform matrix

class UnitShape : public GeometricPrimitive
{
public:
    Mat4 objectToWorld;
    Mat4 worldToObject;

    explicit UnitShape ( Mat4 trans , Material* mat ) : GeometricPrimitive(mat) , objectToWorld(trans) ,worldToObject(trans.invert()) {}

    bool intersect(const Ray &ray, Intersection &record) const override ;
    [[nodiscard]] Vec3f normal_at(const Point3f &surface_point) const override ;

    virtual bool local_intersect (const Ray &ray , Intersection &record ) const = 0;
    [[nodiscard]] virtual Vec3f local_normal_at ( const Point3f &point ) const = 0 ;

    [[nodiscard]] Bounds3f worldBounds() const override;
    [[nodiscard]] virtual Bounds3f objectBounds() const = 0;
};


#endif //RAY_TRACER_UNITSHAPE_H
