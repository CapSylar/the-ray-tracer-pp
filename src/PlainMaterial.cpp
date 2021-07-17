#include "PlainMaterial.h"

Color3f PlainMaterial::get_albedo(Point3f) const
{
    return albedo;
}