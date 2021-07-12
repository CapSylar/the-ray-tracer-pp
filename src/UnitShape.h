#ifndef RAY_TRACER_UNITSHAPE_H
#define RAY_TRACER_UNITSHAPE_H

#include "Material.h"
#include "Mat4.h"
#include "Shape.h"

class Intersection;
class Ray;

// this shape is defined as a unit and then needs and needs to be transformed to the correct position in world space
// by some transform matrix

class UnitShape : public Shape
{
public:
    Mat4 inverse_trans;

    explicit UnitShape ( Mat4 trans , Material* mat ) : Shape(mat) , inverse_trans(trans.invert()) {}

    void intersect(const Ray &ray, std::vector<Intersection> &list) const override ;
    [[nodiscard]] Vec3f normal_at(const Point3f &surface_point) const override ;

};


#endif //RAY_TRACER_UNITSHAPE_H
