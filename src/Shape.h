#ifndef RAY_TRACER_SHAPE_H
#define RAY_TRACER_SHAPE_H

#include <vector>
#include "Vec4.h"

struct Material;
class Ray;
class Intersection;

class Shape
{
public:
    Material* material;

    explicit Shape ( Material *mat ) : material(mat) {}

    virtual void local_intersect ( const Ray &ray , std::vector<Intersection> &list ) const = 0;
    [[nodiscard]] virtual Vector local_normal_at ( const Point &point ) const = 0 ;

    virtual void intersect ( const Ray &ray , std::vector<Intersection>& list ) const;
    [[nodiscard]] virtual Vector normal_at ( const Point &surface_point ) const ;

    ~Shape();

};


#endif //RAY_TRACER_SHAPE_H
