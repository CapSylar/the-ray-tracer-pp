#ifndef RAY_TRACER_POINT3F_H
#define RAY_TRACER_POINT3F_H

#include <iostream>
#include <Vec3f.h>
#include <utilities.h>

class Point3f
{
public:

    Point3f(): x(0),y(0),z(0) {}
    Point3f( float _x , float _y , float _z ) : x(_x),y(_y),z(_z) {}

    float x,y,z;
};

inline
Point3f operator+ ( const Point3f &lhs , const Vec3f &rhs )
{
    return Point3f( lhs.x+rhs.x , lhs.y+rhs.y , lhs.z+rhs.z );
}

inline
Point3f& operator+= ( Point3f &lhs , const Vec3f& rhs )
{
    lhs.x += rhs.x ;
    lhs.y += rhs.y ;
    lhs.z += rhs.z;

    return lhs;
}

inline
Point3f operator- ( const Point3f &lhs , const Vec3f &rhs )
{
    return Point3f( lhs.x - rhs.x , lhs.y - rhs.y , lhs.z - rhs.z );
}

inline
Point3f& operator-= ( Point3f &lhs , const Vec3f& rhs )
{
    lhs.x -= rhs.x ;
    lhs.y -= rhs.y ;
    lhs.z -= rhs.z;

    return lhs;
}

inline
Vec3f operator- ( const Point3f &lhs , const Point3f &rhs )
{
    return Vec3f( lhs.x - rhs.x , lhs.y - rhs.y , lhs.z - rhs.z );
}

inline bool operator== ( const Point3f &lhs , const Point3f &rhs )
{
    return isEqualF(lhs.x,rhs.x) && isEqualF(lhs.y,rhs.y) && isEqualF(lhs.z,rhs.z) ;
}


inline
bool operator!= ( const Point3f &lhs , const Point3f &rhs )
{
    return !( lhs == rhs );
}

inline
std::ostream& operator << ( std::ostream& os , const Point3f &rhs )
{
    os << "{" << rhs.x << "," << rhs.y << "," << rhs.z << "}" ;
    return os;
}

#endif //RAY_TRACER_POINT3F_H
