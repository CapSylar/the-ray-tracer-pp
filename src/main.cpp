#include "Canvas.h"
#include "Ray.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Material.h"

int main ()
{
    Canvas myCanvas(2000,2000 );

    // hacks

    float backside_x = 10;
    float backside_y = 10;

    // pixel size

    double pixel_size_x = backside_x / 2000 ;
    double pixel_size_y = backside_y / 2000 ;

    Sphere s;
    s.transform.scale(1,1,1);

    Material m(Color(1,0,0));
    Light light( Color(1,1,1) , Vec4::getPoint(-10,10,-10));

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

            auto list = s.intersect( ray );

            if ( list.empty() )
            {
                myCanvas.write(Color(0,0,0) , x , y );
                continue;
            }

            auto surface_point = ray.position(Intersection::get_hit(list)->t);
            auto surface_normal = s.normal_at(surface_point);
            auto color = lighting( m , light , surface_point , -ray.direction , surface_normal );

            myCanvas.write( color , x , y );
        }
    }


    myCanvas.save("test_image.ppm");

    return 0;
}