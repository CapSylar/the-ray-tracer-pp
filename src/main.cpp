#include <chrono>

#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Material.h"
#include "World.h"
#include "Cube.h"
#include "Cylinder.h"

int main ()
{
    World cornell_box ;

    Plane floor ( Mat4::IDENTITY() , Material( Color(1 , 1 , 0.8f ))) ;
    Plane right_wall ( Mat4::IDENTITY().rotate_z(M_PI/2).translate(2,0,0) , Material( Color(0,0.9f , 0 )) );
    right_wall.material.specular = 0.4f;
    right_wall.material.shininess = 300 ;

    Plane left_wall ( Mat4::IDENTITY().rotate_z(-M_PI/2).translate(-2,0,0) , Material( Color( 1 , 0 ,0 ))) ;
    left_wall.material.specular = 0.4f;
    left_wall.material.shininess = 300 ;

    Plane back_wall ( Mat4::IDENTITY().rotate_x(-M_PI/2).translate(0,0,3.5f) , Material( Color(1,0,1 ))) ;

    back_wall.material.specular = 0.4f;
    back_wall.material.shininess = 300 ;

    Plane ceiling ( Mat4::IDENTITY().rotate_x(-M_PI).translate(0,3,0) , Material( Color(1,1,0))) ;
    ceiling.material.ambient = 0.3f;

    Plane behind_wall ( Mat4::IDENTITY().rotate_x(M_PI/2).translate(0,0,-2) , Material( Color( 1 , 0 , 1 ))) ;

    behind_wall.material.specular = 0.4f;
    behind_wall.material.shininess = 300 ;

    Light light( Color(1,1,1) , Vec4::getPoint(0,2.5f,1 ));

    // objects

    Sphere glass_ball ( Mat4::IDENTITY().scale(0.5f,0.5f,0.5f).translate(-0.5f,0.5f,1.4f) , Material::getGlassMaterial() );
    glass_ball.material.color = Color(0.2f ,0.2f,0.2f);
    glass_ball.material.reflectance = 1 ;
    glass_ball.material.diffuse = 0.4f;
    glass_ball.material.specular = 1;
    glass_ball.material.shininess = 300 ;

    Sphere air_ball ( Mat4::IDENTITY().scale(0.25f,0.25f,0.25f).translate(-0.5f,0.5f,1.4f) , Material(Color(0,1,1)) );

    Cube mirror_ball ( Mat4::IDENTITY().scale(0.5f,0.5f,0.5f).rotate_y(M_PI/4).rotate_z(M_PI/5).translate(0.5f,1 ,2)  );
    mirror_ball.material.reflectance = 1;
    mirror_ball.material.refractive_index = 1.5f;
    mirror_ball.material.transparency = 1;

    Plane hello ( Mat4::IDENTITY().rotate_x(-M_PI/2).translate(0,0,1) , Material::getGlassMaterial() );
    hello.material.color = Color(0,1 ,0.1f);

    Cylinder cilly ( -2 , 2 , true , Mat4::IDENTITY().scale(0.25f,0.25f,0.25f).rotate_x(M_PI/3).translate(0,1,1.5f));
    cilly.material.reflectance = 1;
    cilly.material.color = Color(0.1f,0.1f,0.1f) ;


    cornell_box.add(light);
    cornell_box.add( floor );
    cornell_box.add( right_wall );
    cornell_box.add( left_wall );
    cornell_box.add( back_wall );
    cornell_box.add( behind_wall );
    cornell_box.add( ceiling ) ;

//    cornell_box.add( glass_ball );
//    cornell_box.add ( mirror_ball );
//    cornell_box.add( air_ball );

    cornell_box.add(cilly);

    Point from = Vec4::getPoint(0,1,-1);
    Point to = Vec4::getPoint(0,1,1);
    Vector up = Vec4::getVector(0,1,0);

    // render the frame
    auto begin = std::chrono::steady_clock::now();

    Camera cam ( 1920 , 1080 , M_PI/2, Mat4::view(from , to , up ) );
    auto canvas = render( cam , cornell_box );

    auto end = std::chrono::steady_clock::now();

    canvas.save("test_image.ppm");

    std::cout << "Render time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

    return 0;
}