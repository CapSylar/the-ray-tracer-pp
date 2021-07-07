#ifndef RAY_TRACER_SHAPE_H
#define RAY_TRACER_SHAPE_H

#include "Material.h"
#include "Mat4.h"

class Intersection;
class Ray;

class Shape
{
public:
    Material* material;
    Mat4 inverse_trans;

    explicit Shape ( Mat4 trans , Material* mat ) : material(mat) , inverse_trans(trans.invert()) {}

    void intersect ( const Ray &ray , std::vector<Intersection>& list ) const ;
    [[nodiscard]] Vector normal_at ( const Point &surface_point ) const ;

    ~Shape()
    {
        delete material;
    }

protected:
    virtual void local_intersect ( const Ray &ray , std::vector<Intersection> &list ) const = 0;
    [[nodiscard]] virtual Vector local_normal_at ( const Point &point ) const = 0 ;
};


#endif //RAY_TRACER_SHAPE_H
