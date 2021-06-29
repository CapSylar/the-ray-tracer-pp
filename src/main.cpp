#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Material.h"
#include "World.h"

int main ()
{
    World cornell_box ;

    Plane floor ( Mat4::IDENTITY() , Material( Color(1 , 0 , 0  ))) ;
    Plane right_wall ( Mat4::IDENTITY().rotate_z(M_PI/2).translate(2,0,0) , Material( Color(1,0 , 0 )) );
    right_wall.material.specular = 0.4f;
    right_wall.material.shininess = 300 ;

    Plane left_wall ( Mat4::IDENTITY().rotate_z(-M_PI/2).translate(-2,0,0) , Material( Color( 1 , 0 ,0 ))) ;
    left_wall.material.specular = 0.4f;
    left_wall.material.shininess = 300 ;

    Plane back_wall ( Mat4::IDENTITY().rotate_x(-M_PI/2).translate(0,0,3.5f) , Material( Color(1,0 , 0))) ;

    back_wall.material.specular = 0.4f;
    back_wall.material.shininess = 300 ;

    Plane ceiling ( Mat4::IDENTITY().rotate_x(-M_PI).translate(0,3,0) , Material( Color(1,0,0))) ;

    Plane behind_wall ( Mat4::IDENTITY().rotate_x(M_PI/2).translate(0,0,-4) , Material( Color( 1 , 0 , 0 ))) ;

    behind_wall.material.specular = 0.4f;
    behind_wall.material.shininess = 300 ;

    Light light( Color(1,1,1) , Vec4::getPoint(0,2.8f,1.75f));

    // objects

    Sphere glass_ball ( Mat4::IDENTITY().scale(0.5,0.5,0.5 ).translate(0,1 ,0 ) , Material::getGlassMaterial() );
    glass_ball.material.color = Color(0 ,0 ,0 );
    glass_ball.material.transparency = 1 ;
//    glass_ball.material.reflectance = 1 ;
    glass_ball.material.diffuse = 0.4f;
    glass_ball.material.specular = 1;
    glass_ball.material.shininess = 300 ;

//    Sphere air_ball ( Mat4::IDENTITY().scale(0.25f,0.25f,0.25f).translate(-1,0.5f,2.5f) , Material(Color(1,0,1)) );

    Sphere mirror_ball ( Mat4::IDENTITY().scale(0.5f,0.5f,0.5f).translate(1,0.5f,2) );
    mirror_ball.material.reflectance = 1;
    mirror_ball.material.color = Color(0,0,0);


    Plane hello ( Mat4::IDENTITY().rotate_x(-M_PI/2).translate(0,0,1) , Material::getGlassMaterial() );
    hello.material.color = Color(0,1 ,0.1f);

    cornell_box.add(light);
    cornell_box.add( floor );
    cornell_box.add( right_wall );
    cornell_box.add( left_wall );
    cornell_box.add( back_wall );
    cornell_box.add( behind_wall );
    cornell_box.add( ceiling ) ;

    cornell_box.add( glass_ball );
//    cornell_box.add ( mirror_ball );
//    cornell_box.add( air_ball ) ;

//      cornell_box.add( hello );


    Point from = Vec4::getPoint(0,1,-2);
    Point to = Vec4::getPoint(0,1,1);
    Vector up = Vec4::getVector(0,1,0);

    Camera cam ( 400 , 400 , M_PI/2, Mat4::view(from , to , up ) );
    auto canvas = render( cam , cornell_box );
    canvas.save("test_image.ppm");

    return 0;
}