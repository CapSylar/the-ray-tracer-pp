#ifndef RAY_TRACER_SHAPE_H
#define RAY_TRACER_SHAPE_H

#include <vector>

struct Material;
class Ray;
class Intersection;

class Vec3f;
class Point3f;

class Shape
{
public:
    Material* material;

    explicit Shape ( Material *mat ) : material(mat) {}

    virtual void local_intersect ( const Ray &ray , std::vector<Intersection> &list ) const = 0;
    [[nodiscard]] virtual Vec3f local_normal_at ( const Point3f &point ) const = 0 ;

    virtual void intersect ( const Ray &ray , std::vector<Intersection>& list ) const;
    [[nodiscard]] virtual Vec3f normal_at ( const Point3f &surface_point ) const ;

    ~Shape();

};


#endif //RAY_TRACER_SHAPE_H
