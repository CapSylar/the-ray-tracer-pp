#include "GeometricPrimitive.h"

#include "Material.h"

std::shared_ptr<const Material> GeometricPrimitive::getMaterial() const
{
    return material;
}

std::shared_ptr<Material> GeometricPrimitive::getMaterial()
{
    return material;
}

void GeometricPrimitive::setMaterial(std::shared_ptr<Material> mat )
{
    material = mat;
}

