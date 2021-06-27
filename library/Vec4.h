#ifndef RAY_TRACER_VEC4_H
#define RAY_TRACER_VEC4_H

#include <limits>
#include <cmath>
#include <iostream>

struct Vec4;
using Point = Vec4 ;
using Vector = Vec4 ;

struct Vec4
{
public:
    float x,y,z,w;

    explicit Vec4 ( float xx = 0 , float yy = 0 , float zz = 0 , float ww = 0 ) : x(xx) , y(yy) , z(zz) , w(ww) {}

    static Vec4 getPoint(float x = 0 , float y = 0 , float z = 0 );
    static Vec4 getVector(float x = 0 , float y = 0 , float z = 0 );

    Vec4 operator-() const ;
    float magnitude() const ;
    Vec4 normalize_copy() const ;

    Vec4& normalize() ;
    static Vec4 cross ( const Vec4& lhs , const Vec4& rhs ) ;
};

Vec4 operator+ ( const Vec4 &lhs , const Vec4 &rhs );
Vec4 operator- ( const Vec4 &lhs , const Vec4 &rhs );
bool operator== ( const Vec4 &lhs , const Vec4 &rhs );
bool operator!= ( const Vec4 &lhs , const Vec4 &rhs );
Vec4 operator * ( const Vec4 &lhs , float rhs );
Vec4 operator * ( float lhs , const Vec4 &rhs );
float operator * ( const Vec4 &lhs , const Vec4 &rhs );
Vec4 operator / ( const Vec4 &lhs , float rhs );
std::ostream& operator << ( std::ostream& os , const Vec4 &rhs );

#endif //RAY_TRACER_VEC4_H
