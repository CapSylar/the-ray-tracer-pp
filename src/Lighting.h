#ifndef RAY_TRACER_LIGHTING_H
#define RAY_TRACER_LIGHTING_H

class World;
class Ray;
struct Color;
struct Material;
struct LightComputations;
struct Light;
struct Vec4;

using Point = Vec4;
using Vector = Vec4;

namespace Lighting
{
    Color get_surface_color (const Light &light , const LightComputations &comps , bool in_shadow );
    Color color_at(const World &world, const Ray &ray, bool calc_shadow, int remaining = 4 );
    bool is_shadowed( const World &world , const Point &point );
    Color get_reflected_color(const World &world, const LightComputations &comps, int remaining = 4 );
    Color get_refracted_color ( const World &world , const LightComputations &comps , int remaining = 4 );
    float get_schlick_factor ( const LightComputations &comps );
    Color shade_hit ( const World &world , const LightComputations &comps , bool calc_shadow , int remaining = 4 );
}

#endif //RAY_TRACER_LIGHTING_H
