#include "GeometricPrimitive.h"

#include "Material.h"

const Material *GeometricPrimitive::getMaterial() const
{
    return material;
}

GeometricPrimitive::~GeometricPrimitive()
{
    delete material;
}
