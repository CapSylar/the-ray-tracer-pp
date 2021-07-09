#ifndef RAY_TRACER_CYLINDER_H
#define RAY_TRACER_CYLINDER_H

#include "UnitShape.h"

class Cylinder : public UnitShape
{
public:

    float min , max ;
    bool is_capped ;

    explicit Cylinder (  Material *mat , float minimum = -INFINITY, float maximum = INFINITY , bool capped = false , Mat4 trans = Mat4() ) :
        UnitShape ( trans , mat ), min(minimum) , max(maximum) , is_capped(capped) {}

    void local_intersect(const Ray &ray, std::vector<Intersection> &list) const override;
    [[nodiscard]] Vector local_normal_at(const Point &point) const override;


private:
    [[nodiscard]] static bool check_cap ( const Ray &ray , float t ) ;
    void intersect_caps ( const Ray &ray , std::vector<Intersection> &list ) const ;
};


#endif //RAY_TRACER_CYLINDER_H
