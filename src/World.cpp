#include "World.h"

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
