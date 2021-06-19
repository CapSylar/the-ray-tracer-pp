#include "Canvas.h"
#include "Mat4.h"
#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"

int main ()
{
    Canvas myCanvas(500,500);

    // hacks

    float backside_x = 10;
    float backside_y = 10;

    // pixel size

    double pixel_size_x = backside_x / 500 ;
    double pixel_size_y = backside_y / 500 ;

    Sphere s;
    s.transform.scale(1,1,1);

    for ( int x = 0 ; x < 500 ; ++x )
    {
        for ( int y = 0 ; y < 500 ; ++y  )
        {
            float world_x = -backside_x/2 + x * pixel_size_x ;
            float world_y = backside_y/2 - y * pixel_size_y ;
            // produce ray from camera position at x = 0 , y = 0 z = -10 to plane placed at 10
            Point current = Vec4::getPoint(0,0,-5);
            Point point_on_plane = Vec4::getPoint( world_x , world_y , 10 );

            Vector cam_to_plane = point_on_plane - current;
            cam_to_plane.normalize();
            Ray ray( current , cam_to_plane );

            auto list = s.intersect( ray );
            myCanvas.write( list.empty() ? Vec4::getColor(0,0,0) : Vec4::getColor(1,0,0)  , x , y );
        }
    }


    myCanvas.save("test_image.ppm");

    return 0;
}