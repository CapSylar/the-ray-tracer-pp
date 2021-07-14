#ifndef RAY_TRACER_VEC3F_H
#define RAY_TRACER_VEC3F_H

#include <limits>
#include <cmath>
#include <iostream>
#include "utilities.h"
#include "cassert"

class Point3f;

class Vec3f
{
public:
    Vec3f() { x=y=z=0;}
    Vec3f(float _x , float _y , float _z ) : x(_x) , y(_y) , z(_z)
    {
        assert(!HasNaNs());
    }
    explicit Vec3f ( const Point3f &point ) ;

    Vec3f operator-() const ;
    Vec3f& operator=( const Point3f &point );
    float operator[](int i) const;
    float& operator[](int i);
    [[nodiscard]] float length() const ;
    [[nodiscard]] float lengthSquare() const;
    Vec3f& normalize();
    [[nodiscard]] Vec3f normalize_copy() const;

    float x,y,z;

private:
    [[nodiscard]] bool HasNaNs() const
    {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }
};

inline
float Vec3f::lengthSquare() const
{
    return x*x + y*y + z*z;
}
inline
float Vec3f::length() const
{
    return std::sqrt(lengthSquare());
}
inline
Vec3f Vec3f::operator-() const
{
    return Vec3f(-x,-y,-z);
}
inline
Vec3f &Vec3f::normalize()
{
    // normalize in place
    const auto len = length();
    x /= len;
    y /= len;
    z /= len;

    return *this;
}

inline
Vec3f operator * ( const Vec3f &lhs , float rhs )
{
    return Vec3f( lhs.x * rhs , lhs.y * rhs, lhs.z * rhs);
}

inline
Vec3f operator / ( const Vec3f &lhs , float rhs )
{
    assert(rhs!=0);
    const auto inv = 1 / rhs ;
    return lhs * inv ;
}

inline
Vec3f Vec3f::normalize_copy() const
{
    return *this / length() ;
}

float& Vec3f::operator[](int i)
{
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
}

float Vec3f::operator[](int i) const
{
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
}

inline
Vec3f operator+ ( const Vec3f &lhs , const Vec3f &rhs )
{
    return Vec3f( lhs.x + rhs.x , lhs.y + rhs.y , lhs.z + rhs.z );
}
inline
Vec3f operator- ( const Vec3f &lhs , const Vec3f &rhs )
{
    return Vec3f ( lhs.x - rhs.x , lhs.y - rhs.y , lhs.z - rhs.z );
}
inline
bool operator== ( const Vec3f &lhs , const Vec3f &rhs )
{
    return isEqualF(lhs.x,rhs.x) && isEqualF(lhs.y,rhs.y) && isEqualF(lhs.z,rhs.z) ;
}
inline
bool operator!= ( const Vec3f &lhs , const Vec3f &rhs )
{
    return !( lhs == rhs );
}

inline
Vec3f operator * ( float lhs , const Vec3f &rhs )
{
    return rhs * lhs;
}
inline
float operator * ( const Vec3f &lhs , const Vec3f &rhs )
{
    // dot product
    return  lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z ;
}
inline
std::ostream& operator << ( std::ostream& os , const Vec3f &rhs )
{

    os << "{" << rhs.x << "," << rhs.y << "," << rhs.z << "}" ;
    return os;
}
inline
Vec3f cross ( const Vec3f& lhs , const Vec3f& rhs )
{
    // cross product between lhs and rhs
    return Vec3f( lhs.y * rhs.z - lhs.z * rhs.y,
                  lhs.z * rhs.x - lhs.x * rhs.z,
                  lhs.x * rhs.y - lhs.y * rhs.x);
}


#endif //RAY_TRACER_VEC3F_H
