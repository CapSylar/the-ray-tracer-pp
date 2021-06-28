#include "Material.h"

bool operator == ( const Material &lhs , const Material &rhs )
{
    return (lhs.specular == rhs.specular &&
            lhs.diffuse == rhs.diffuse &&
            lhs.ambient == rhs.ambient &&
            lhs.shininess == rhs.shininess &&
            lhs.reflectance == rhs.reflectance &&
            lhs.color == rhs.color );
}

