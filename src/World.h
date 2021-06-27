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

    void add ( Shape &shape )
    {
        objects.push_back(&shape);
    }

    void add ( Light &light )
    {
        lights.push_back(&light);
    }

    Light& getLight() const
    {
        return *(lights[0]);
    }

    std::vector<Intersection> intersect ( const Ray &ray ) const ;

private:
    std::vector<Shape *> objects;
    //TODO: for now we only have a single light source, to extend this in the future
    std::vector<Light *> lights;
};

Canvas render( const Camera& cam , const World &world );

#endif //RAY_TRACER_WORLD_H
