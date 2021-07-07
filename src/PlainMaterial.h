#ifndef RAY_TRACER_PLAINMATERIAL_H
#define RAY_TRACER_PLAINMATERIAL_H

#include "Material.h"

struct PlainMaterial : public Material
{
    Color albedo; // this material has the same base color everywhere

    template<typename... Args>
    explicit PlainMaterial ( Color color = Color() , Args... args  ) :Material(std::forward<Args>(args)...), albedo(color)  {}

    Color get_albedo(Point) override ;

    //TODO: does this belong here ???
    static PlainMaterial* getGlassMaterial();

};

#endif //RAY_TRACER_PLAINMATERIAL_H
