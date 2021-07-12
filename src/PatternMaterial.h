#ifndef RAY_TRACER_PATTERNMATERIAL_H
#define RAY_TRACER_PATTERNMATERIAL_H

#include "Mat4.h"
#include "Material.h"

struct ColorPattern;
struct UnitShape;


struct PatternMaterial : public Material
{
    Mat4 inverse_trans;
    const ColorPattern* pattern;

    template<typename... Args>
    explicit PatternMaterial ( const ColorPattern *Pattern , Args... args  ) : Material(std::forward<Args>(args)...), pattern(Pattern) {}

    Color3f get_albedo(Point3f point_on_surface) override;
};


#endif //RAY_TRACER_PATTERNMATERIAL_H
