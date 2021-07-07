#include "Material.h"

bool operator == ( const Material &lhs , const Material &rhs )
{
    return (lhs.specular == rhs.specular &&
            lhs.diffuse == rhs.diffuse &&
            lhs.ambient == rhs.ambient &&
            lhs.shininess == rhs.shininess &&
            lhs.reflectance == rhs.reflectance &&
            lhs.refractive_index == rhs.refractive_index &&
            lhs.transparency == rhs.transparency );
}

//Material Material::getGlassMaterial()
//{
//    // return a glassy material with refractive index of 1.5
//    return Material(  0.1 , 0.9 , 0.9 , 200 , 0 , 1 , 1.5f  );
//}