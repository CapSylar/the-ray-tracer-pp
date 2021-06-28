#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Material.h"
#include "World.h"

int main ()
{
    World w;

    Sphere s ( Mat4::IDENTITY().scale(0.5,0.5,0.5).translate(-1.5f,0.5,0 )  , Material(Color(0.3f,0,0)) );
    s.material.reflectance = 0.9f;
    Sphere s1 ( Mat4::IDENTITY().scale(0.5,0.5,0.5).translate(0.3,0.5,-2) , Material(Color(0.3f,0,0)) );
    s1.material.reflectance = 0.9f ;

    Sphere s2 ( Mat4::IDENTITY().scale(0.5,0.5,0.5).translate(0.8,0.5,-1) , Material(Color(0.3f,0,0)) );
    s1.material.reflectance = 0.9f ;

    Sphere s3 ( Mat4::IDENTITY().scale(0.5,0.5,0.5).translate(-.075f,0.5,+1) , Material(Color(0.3f,0,0)) );
    s1.material.reflectance = 0.9f ;

    Plane p;
    p.material.color = Color(0.1,0.2,0.5f) ;
    p.material.reflectance = 0.3f;

    Light light( Color(1,1,1) , Vec4::getPoint(0,100,-10));

    w.add( s );
    w.add ( s1 );
    w.add ( p );
    w.add ( light );
    w.add(s2);
    w.add(s3);

    Point from = Vec4::getPoint(1,1,-4);
    Point to = Vec4::getPoint(0,0,0);
    Vector up = Vec4::getVector(0,1,0);

    Camera cam ( 1920 , 1080 , M_PI/2, Mat4::view(from , to , up) );
    auto canvas = render( cam , w );
    canvas.save("test_image.ppm");

    return 0;
}