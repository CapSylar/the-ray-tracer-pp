#ifndef RAY_TRACER_PRIMITIVE_H
#define RAY_TRACER_PRIMITIVE_H

#include <vector>

struct Material;
class Ray;
class Intersection;

class Vec3f;
class Point3f;
class Bounds3f;

class Primitive
{
public:

    [[nodiscard]] virtual const Material* getMaterial() const = 0;
    virtual Material* getMaterial() = 0;
    virtual void intersect ( const Ray &ray , std::vector<Intersection>& list ) const = 0;
    [[nodiscard]] virtual Vec3f normal_at ( const Point3f &surface_point ) const = 0 ;
    [[nodiscard]] virtual Bounds3f worldBounds() const = 0;
};

#endif //RAY_TRACER_PRIMITIVE_H
