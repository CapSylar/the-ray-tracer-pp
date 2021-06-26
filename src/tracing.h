#ifndef RAY_TRACER_TRACING_H
#define RAY_TRACER_TRACING_H

#include "Color.h"
#include "Material.h"
#include "Intersection.h"
#include "World.h"

namespace Lighting
{
    Color lighting ( const Material &material , const Light &light , const Point &point , const Vector &eye , const Vector &normal , bool in_shadow );
    Color color_at(const World &world, const Ray &ray , bool calc_shadow = false );
    bool is_shadowed( const World &world , const Point &point );
}

#endif //RAY_TRACER_TRACING_H
