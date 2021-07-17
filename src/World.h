#ifndef RAY_TRACER_WORLD_H
#define RAY_TRACER_WORLD_H

#include <vector>
#include <algorithm>
#include "Sphere.h"
#include "Material.h"
#include "Ray.h"
#include "Intersection.h"
#include "Camera.h"
#include "Canvas.h"

class World
{
public:
    World() = default;

    void add ( std::shared_ptr<Primitive> &&primitive )
    {
        objects.push_back(primitive);
    }

    void add ( std::shared_ptr<Light> &&light )
    {
        lights.push_back(light);
    }

    [[nodiscard]] Light& getLight() const
    {
        return *(lights[0]);
    }

    [[nodiscard]] bool intersect(const Ray &ray, Intersection &record) const; // used for normal rays
    bool intersectP ( const Ray &ray , Intersection &record ) const; // used for shadown rays

private:
    std::vector<std::shared_ptr<Primitive>> objects;
    std::vector<std::shared_ptr<Light>> lights;
};

Canvas render( const Camera& cam , const World &world );

#endif //RAY_TRACER_WORLD_H
