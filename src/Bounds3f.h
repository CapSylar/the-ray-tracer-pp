#ifndef RAY_TRACER_BOUNDS3F_H
#define RAY_TRACER_BOUNDS3F_H

#include "Point3f.h"
#include <limits>

class Bounds3f
{
private:
    static constexpr float min = std::numeric_limits<float>::lowest() ;
    static constexpr float max = std::numeric_limits<float>::max() ;


public:
    Bounds3f() ;
    Bounds3f( const Point3f &p1 , const Point3f &p2 );

    Vec3f diagonal() const;
    int maximumExtent() const;

    Point3f pMin , pMax;
};

inline
bool operator== ( const Bounds3f &lhs , const Bounds3f &rhs )
{
    return ( lhs.pMin == rhs.pMin && rhs.pMin == rhs.pMax );
}

inline
bool operator!= ( const Bounds3f &lhs , const Bounds3f &rhs )
{
    return !(lhs == rhs);
}

Bounds3f Union ( const Bounds3f &b , const Point3f &p );
Bounds3f Union ( const Bounds3f &b1 , const Bounds3f &b2 );

#endif //RAY_TRACER_BOUNDS3F_H
