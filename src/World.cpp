#define OMP_NUM_THREADS 10

#include "World.h"
#include "Camera.h"
#include "Canvas.h"
#include "Lighting.h"

bool World::intersect(const Ray &ray, Intersection &record) const
{
    // intersect each object in the world
    bool flag = false;
    for ( const auto &obj : objects )
    {
        bool didIntersect = obj->intersect( ray , record );
        if ( !flag ) flag = didIntersect;
    }

    return flag;
}

bool World::intersectP(const Ray &ray, Intersection &record) const
{
    for ( const auto &obj : objects )
    {
        if ( obj->intersect( ray , record )) // we just care if an object is present that occludes the light source
            return true;
    }

    return false;
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
                        Color3f c = Lighting::color_at(world, ray, true , 15 );
                        canvas.write( c , x + x_inside  , y + y_inside );
                    }
                }
                x += upperBoundX-1; // -1 to account for ++x
            }
            y += upperBoundY-1; // -1 to account for ++y
        }
    }


    return canvas;
}
