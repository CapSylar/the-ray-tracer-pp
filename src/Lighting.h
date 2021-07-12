#ifndef RAY_TRACER_LIGHTING_H
#define RAY_TRACER_LIGHTING_H

class World;
class Ray;
struct Color3f;
struct Material;
struct LightComputations;
struct Light;

class Vec3f;
class Point3f;

namespace Lighting
{
    Color3f get_surface_color (const Light &light , const LightComputations &comps , bool in_shadow );
    Color3f color_at(const World &world, const Ray &ray, bool calc_shadow, int remaining = 4 );
    bool is_shadowed( const World &world , const Point3f &point );
    Color3f get_reflected_color(const World &world, const LightComputations &comps, int remaining = 4 );
    Color3f get_refracted_color ( const World &world , const LightComputations &comps , int remaining = 4 );
    float get_schlick_factor ( const LightComputations &comps );
    Color3f shade_hit ( const World &world , const LightComputations &comps , bool calc_shadow , int remaining = 4 );
}

#endif //RAY_TRACER_LIGHTING_H
