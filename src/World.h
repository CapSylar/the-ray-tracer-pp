#ifndef RAY_TRACER_WORLD_H
#define RAY_TRACER_WORLD_H

#include <vector>
#include <algorithm>
#include "Sphere.h"
#include "Material.h"
#include "Ray.h"
#include "Intersection.h"

class World
{
public:
    World() = default;

    void add ( Sphere &sphere )
    {
        objects.push_back(&sphere);
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
    std::vector<Sphere *> objects;
    //TODO: for now we only have a single light source, to extend this in the future
    std::vector<Light *> lights;
};



#endif //RAY_TRACER_WORLD_H
