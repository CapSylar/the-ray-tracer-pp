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
