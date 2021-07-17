#ifndef RAY_TRACER_CYLINDER_H
#define RAY_TRACER_CYLINDER_H

#include "UnitShape.h"

class Cylinder : public UnitShape
{
public:

    float zMin , zMax ;
    bool is_capped ;

    explicit Cylinder (  Material *mat , float minimum = -INFINITY, float maximum = INFINITY , bool capped = false , Mat4 trans = Mat4() ) :
            UnitShape ( trans , mat ), zMin(minimum) , zMax(maximum) , is_capped(capped) {}

    bool local_intersect(const Ray &ray, Intersection &record) const override;
    [[nodiscard]] Vec3f local_normal_at(const Point3f &point) const override;

    [[nodiscard]] Bounds3f objectBounds() const override;


private:
    [[nodiscard]] static bool check_cap ( const Ray &ray , float t ) ;
    bool intersect_caps (const Ray &ray , Intersection &record ) const ;
};


#endif //RAY_TRACER_CYLINDER_H
