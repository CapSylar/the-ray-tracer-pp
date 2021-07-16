#define OMP_NUM_THREADS 10

#include "World.h"
#include "Camera.h"
#include "Canvas.h"
#include "Lighting.h"

std::vector<Intersection> World::intersect(const Ray &ray) const
{
    std::vector<Intersection> list;
    // intersect each object in the world and put all the intersections in the vector
    for ( const auto obj : objects )
    {
        obj->intersect( ray  , list );
    }

    // sort them before returning, because hit() assumes them already sorted
    std::sort( list.begin() , list.end() );
    return list;
}

Canvas render( const Camera& cam , const World &world )
{
    Canvas canvas( cam.getHSize() , cam.getVSize() );

#pragma omp parallel default(none) shared(cam, world , canvas)  num_threads(OMP_NUM_THREADS)
    {
#pragma omp for schedule(dynamic,10) // 10 magic number, experiment with this

        // 32x32 ray packets in an attempt to improve performance through cache access improvement since
        // closer rays are more likely to intersect the same objects hence may have same memory accesses

        for ( int y = 0 ; y < cam.getVSize() ; ++y )
        {
            const auto upperBoundY = (cam.getVSize() - 32 - y >= 0 ? 32 : cam.getVSize() - 32 - y ) ;

            for ( int x = 0 ; x < cam.getHSize(); ++x )
            {
                const auto upperBoundX = (cam.getHSize() - 32 - x >= 0 ? 32 : cam.getHSize() - 32 - x ) ;

                for ( int y_inside = 0 ; y_inside < upperBoundY ; ++y_inside )
                {
                    for (int x_inside = 0 ; x_inside < upperBoundX ; ++x_inside )
                    {
                        auto ray = cam.getRayForPixel( x + x_inside , y + y_inside );
                        Color3f c = Lighting::color_at(world, ray, true , 5 );
                        canvas.write( c , x + x_inside  , y + y_inside );
                    }
                }
                x += upperBoundX-1; // -1 to account for ++x
            }
            y += upperBoundY-1;
        }
    }


    return canvas;
}
