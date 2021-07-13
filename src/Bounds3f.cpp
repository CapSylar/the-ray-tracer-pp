#include "Bounds3f.h"

#include <limits>

Bounds3f::Bounds3f()
{
    // invalid configuration on purpose
    pMin = Point3f( max , max , max );
    pMax = Point3f( min , min , min );
}

Bounds3f::Bounds3f(const Point3f &p1, const Point3f &p2)
{
    // find the component-wise min and max since we can't guarantee that p1 and p2 are passed in the correct order
    pMin = Point3f( std::min(p1.x,p2.x) , std::min(p1.y,p2.y) , std::min(p1.z,p2.z));
    pMax = Point3f( std::max(p1.x,p2.x) , std::max(p1.y,p2.y) , std::max(p1.z,p2.z));
}

Vec3f Bounds3f::diagonal() const
{
    return pMax - pMin ;
}

int Bounds3f::maximumExtent() const
{
    // return the index of which of the three axes in the longest , 0 is X, 1 is Y , 2 is Z
    const auto d = diagonal();
    return (d.x > d.y)? ( d.x > d.z ? 0 : 2 ) : ( d.y > d.z ? 1 : 2 ) ;
}

Bounds3f Union ( const Bounds3f &b , const Point3f &p )
{
    // return a box that encloses the point
    return  Bounds3f( Point3f(std::min(b.pMin.x,p.x) , std::min(b.pMin.y,p.y)  , std::min(b.pMin.z,p.z)),
                      Point3f(std::min(b.pMax.x , p.x) , std::min(b.pMax.y , p.y) , std::min(b.pMax.z , p.z) ));
}

Bounds3f Union ( const Bounds3f &b1 , const Bounds3f &b2 )
{
    // return a box that in the union of the two boxes
    return  Bounds3f( Point3f(std::min(b1.pMin.x,b2.pMin.x) , std::min(b1.pMin.y,b2.pMin.y)  , std::min(b1.pMin.z,b2.pMin.z)),
                      Point3f(std::min(b1.pMax.x , b2.pMax.x) , std::min(b1.pMax.y , b2.pMax.y) , std::min(b1.pMax.z , b2.pMax.z) ));
}

Bounds3f Intersect ( const Bounds3f &b1 , const Bounds3f &b2 )
{
    // return a box that is the intersection of the two boxes
    return Bounds3f( Point3f( std::max(b1.pMin.x , b2.pMin.x) , std::max ( b1.pMin.y , b2.pMin.y) , std::max(b1.pMin.z,b2.pMin.z) ) ,
                     Point3f( std::min(b1.pMax.x , b2.pMax.x) , std::min ( b1.pMax.y , b2.pMax.y) , std::min(b1.pMax.z,b2.pMax.z) ) );
}
