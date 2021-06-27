//TODO: the two following operations result in unwanted behavior if we ,
// subtract a getPoint from a vector or if we add two points, make them safer
// to use

#include "Vec4.h"
#include "utilities.h"

Vec4 operator+ ( const Vec4 &lhs , const Vec4 &rhs )
{
    return Vec4(lhs.x + rhs.x,lhs.y+rhs.y,lhs.z+rhs.z,lhs.w+rhs.w);
}

Vec4 operator- ( const Vec4 &lhs , const Vec4 &rhs )
{
    return Vec4(lhs.x-rhs.x,lhs.y-rhs.y,lhs.z-rhs.z,lhs.w-rhs.w);
}

bool operator== ( const Vec4 &lhs , const Vec4 &rhs )
{
//    static constexpr auto eps = std::numeric_limits<float>::epsilon();
    // compare the two Vec4s element-wise

    return (isEqual_f(lhs.x,rhs.x)&&
            isEqual_f(lhs.y,rhs.y)&&
            isEqual_f(lhs.z,rhs.z)&&
            isEqual_f(lhs.w,rhs.w));
}

bool operator!= ( const Vec4 &lhs , const Vec4 &rhs )
{
    return !(lhs==rhs);
}

Vec4 operator * ( const Vec4 &lhs , float rhs ) // vector * scalar
{
    return Vec4( lhs.x * rhs , lhs.y * rhs , lhs.z * rhs , lhs.w );
}

Vec4 operator * ( float lhs , const Vec4 &rhs ) // scalar * vector
{
    return Vec4( rhs.x * lhs , rhs.y * lhs , rhs.z * lhs , rhs.w );
}

float operator * ( const Vec4 &lhs , const Vec4 &rhs ) // dot product
{
    // TODO: only works for vectors, should not be used on points
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z ;
}

Vec4 operator / ( const Vec4 &lhs , float rhs )
{
    return lhs * (1/rhs);
}

std::ostream& operator << ( std::ostream& os , const Vec4 &rhs )
{
    os << "[" << rhs.x << "," << rhs.y << "," << rhs.z << "," << rhs.w << "]";

    return os;
}

Vec4 Vec4::cross ( const Vec4& lhs , const Vec4& rhs )
{
    // cross product between lhs and rhs
    return Vec4( lhs.y * rhs.z - lhs.z * rhs.y,
                 lhs.z * rhs.x - lhs.x * rhs.z,
                 lhs.x * rhs.y - lhs.y * rhs.x);
}

Vec4& Vec4::normalize()
{
    const auto mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;

    return *this;
}

Vec4 Vec4::getPoint(float x, float y, float z)
{
    return Vec4(x,y,z,1);
}

Vec4 Vec4::getVector(float x , float y , float z)
{
    return Vec4(x ,y , z , 0 );
}

Vec4 Vec4::operator- () const
{
    // return a new negated copy
    return Vec4(-x,-y,-z,w);
}

float Vec4::magnitude() const
{
    return sqrt(x*x+y*y+z*z);
}

Vec4 Vec4::normalize_copy() const
{
    return Vec4(x,y,z,w).normalize();
}

