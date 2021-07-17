#ifndef RAY_TRACER_PRIMITIVE_H
#define RAY_TRACER_PRIMITIVE_H

#include <vector>
#include <memory>

struct Material;
class Ray;
class Intersection;

class Vec3f;
class Point3f;
class Bounds3f;

class Primitive
{
public:

    [[nodiscard]] virtual std::shared_ptr<const Material> getMaterial() const = 0;
    virtual std::shared_ptr<Material> getMaterial() = 0;
    virtual void setMaterial( std::shared_ptr<Material> material ) = 0;

    virtual bool intersect (const Ray &ray , Intersection &record ) const = 0;
    [[nodiscard]] virtual Vec3f normal_at ( const Point3f &surface_point ) const = 0 ;
    [[nodiscard]] virtual Bounds3f worldBounds() const = 0;
};

#endif //RAY_TRACER_PRIMITIVE_H
