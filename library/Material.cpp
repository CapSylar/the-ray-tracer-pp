#include "Material.h"
#include "Ray.h"

Color lighting ( const Material &material , const Light &light , const Point &point , const Vector &eye , const Vector &normal )
{
    Color base_color = material.color * light.intensity; // base color made up of the light color and material color

    // calculate lightv as vector vector from point to the light source
    Vector lightv = light.position - point ;
    lightv.normalize();

    Color ambient = base_color * material.ambient ;

    // lightv and normal are both normalized vectors
    float cosine = lightv * normal ;

    if ( cosine < 0 ) // light source is on the other side of the surface
        return ambient;

    Color diffuse = base_color * material.diffuse * cosine ;

    Vector reflectv = Ray::reflect( -lightv , normal );
    float reflect_dot_eye = reflectv * eye ;

    if ( reflect_dot_eye < 0 ) // neglect the specular component
        return ambient + diffuse ;

    Color specular = light.intensity * material.specular * powf(reflect_dot_eye,material.shininess);

    return ambient + diffuse + specular;
}