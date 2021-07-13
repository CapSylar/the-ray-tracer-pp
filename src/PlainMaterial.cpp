#include "PlainMaterial.h"

Color3f PlainMaterial::get_albedo(Point3f) const
{
    return albedo;
}

PlainMaterial *PlainMaterial::getGlassMaterial()
{
    return new PlainMaterial ( Color3f(0,0,0), 0.1 , 0.9 , 0.9 , 200 , 0 , 1 , 1.5f  );
}
