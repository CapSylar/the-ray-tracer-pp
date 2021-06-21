#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H

#include "Vec4.h"
#include "Color.h"

struct Material
{
    explicit Material( Color coco = Color() , float Ambient = 0.1 , float Diffuse = 0.9 , float Specular = 0.9 , float Shininess = 200 ) :
        color(coco), ambient(Ambient) , diffuse(Diffuse) , specular(Specular) , shininess(Shininess)
    {}

    Color color;
    float ambient,diffuse,specular,shininess;
};

struct Light
{
    Color intensity;
    Point position;

    Light( Color intensity , Point position ) : intensity(intensity) , position(position) {}
};


#endif //RAY_TRACER_MATERIAL_H
