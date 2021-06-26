#include "Ray.h"
#include "Sphere.h"
#include "Material.h"
#include "World.h"

int main ()
{
    World w;

    Sphere s ( Material(Color(1,0,0)) , Mat4::IDENTITY().scale(1,1,1) );
    Sphere s1 ( Material(Color(0,1,0)) , Mat4::IDENTITY().scale(0.5,0.5,0.5).translate(0.3,0,-2) );

    Light light( Color(1,1,1) , Vec4::getPoint(-10,10,-10));

    w.add( s );
    w.add ( s1 );
    w.add ( light );

    Point from = Vec4::getPoint(4,1.5f,-5);
    Point to = Vec4::getPoint(0,0,0);
    Vector up = Vec4::getVector(0,1,0);

    Camera cam ( 1000 , 1000 , M_PI/2, Mat4::view(from , to , up) );
    auto canvas = render( cam , w );
    canvas.save("test_image.ppm");

    return 0;
}