#include "PlainMaterial.h"

Color PlainMaterial::get_albedo(Point)
{
    return albedo;
}

PlainMaterial *PlainMaterial::getGlassMaterial()
{
    return new PlainMaterial ( Color(0,0,0), 0.1 , 0.9 , 0.9 , 200 , 0 , 1 , 1.5f  );
}
