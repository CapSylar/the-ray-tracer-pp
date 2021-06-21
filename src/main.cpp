#include "Canvas.h"
#include "Ray.h"
#include "Sphere.h"
#include "Material.h"
#include "World.h"
#include "tracing.h"

int main ()
{
    Canvas myCanvas(2000,2000 );

    // hacks

    float backside_x = 20;
    float backside_y = 20;

    // pixel size

    double pixel_size_x = backside_x / 2000 ;
    double pixel_size_y = backside_y / 2000 ;

    World w;

    Sphere s ( Material(Color(1,0,0)) , Mat4::IDENTITY().scale(1,1,1) );
    Sphere s1 ( Material(Color(0,1,0)) , Mat4::IDENTITY().scale(0.5,0.5,0.5).translate(0.3,0,-2) );

    Light light( Color(1,1,1) , Vec4::getPoint(-10,10,-10));

    w.add( s );
    w.add ( s1 );
    w.add ( light );

    for ( int x = 0 ; x < 2000 ; ++x )
    {
        for ( int y = 0 ; y < 2000 ; ++y  )
        {
            float world_x = -backside_x/2 + x * pixel_size_x ;
            float world_y = backside_y/2 - y * pixel_size_y ;
            // produce ray from camera position at x = 0 , y = 0 z = -10 to plane placed at 10
            Point current = Vec4::getPoint(0,0,-5);
            Point point_on_plane = Vec4::getPoint( world_x , world_y , 10 );

            Vector cam_to_plane = point_on_plane - current;
            cam_to_plane.normalize();
            Ray ray( current , cam_to_plane );

            auto color = Lighting::color_at( w , ray ) ;
            myCanvas.write( color , x , y );
        }
    }


    myCanvas.save("test_image.ppm");

    return 0;
}