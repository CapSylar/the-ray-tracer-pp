#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H

#include "Vec4.h"
#include "Color.h"

struct Material
{
    explicit Material( float Ambient = 0.1 , float Diffuse = 0.9 , float Specular = 0.9f , float Shininess = 200 , float Reflectance = 0 ,
                       float Transparency = 0.0f , float Refractive_index = 1.0f ) : ambient(Ambient) , diffuse(Diffuse) , specular(Specular) , shininess(Shininess) , reflectance(Reflectance) , transparency(Transparency),
        refractive_index(Refractive_index)
    {}

    float ambient,diffuse,specular,shininess,reflectance, transparency, refractive_index ;
    virtual Color get_albedo( Point point_on_surface ) = 0;

    virtual ~Material() = default;
};

bool operator == ( const Material &lhs , const Material &rhs ) ;

struct Light
{
    Color intensity;
    Point position;

    Light( Color intensity , Point position ) : intensity(intensity) , position(position) {}
};

#endif //RAY_TRACER_MATERIAL_H
