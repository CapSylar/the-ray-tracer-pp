#ifndef RAY_TRACER_PLAINMATERIAL_H
#define RAY_TRACER_PLAINMATERIAL_H

#include "Material.h"

struct PlainMaterial : public Material
{
    Color3f albedo; // this material has the same base color everywhere

    template<typename... Args>
    explicit PlainMaterial ( Color3f color = Color3f() , Args... args  ) :Material(std::forward<Args>(args)...), albedo(color)  {}

    [[nodiscard]] Color3f get_albedo(Point3f) const override ;
};

#endif //RAY_TRACER_PLAINMATERIAL_H
