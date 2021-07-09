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

#pragma omp parallel default(none) shared(cam, world , canvas) num_threads(12)
    {
#pragma omp for schedule(dynamic,10) // 10 magic number, experiment with this
        for ( int y = 0 ; y < cam.getVSize() ; ++y )
        {
            for ( int x = 0 ; x < cam.getHSize() ; ++x )
            {
                auto ray = cam.getRayForPixel( x , y );
                Color c = Lighting::color_at(world, ray, true , 5 );
                canvas.write( c , x , y );
            }
        }
    }


    return canvas;
}
