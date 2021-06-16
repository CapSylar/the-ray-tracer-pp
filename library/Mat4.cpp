#include "Mat4.h"
#include "Vec4.h"
#include "utilities.h"

bool operator == ( const Mat4 &lhs , const Mat4 &rhs )
{
    for ( int i = 0 ; i < 16 ; ++i )
    {
        if (!isEqual_f(lhs.m[i],rhs.m[i]))
            return false;
    }

    return true;
}

Mat4 operator * ( const Mat4 &lhs , const Mat4 &rhs )
{
    Mat4 toReturn;
    for ( int row = 0 ; row < 4 ; ++row )
    {
        for (int col = 0; col < 4; ++col)
        {
            toReturn.m[col + row * 4] = lhs.m[row * 4] * rhs.m[col] + lhs.m[row * 4 + 1] * rhs.m[4 + col] +
                                        lhs.m[row * 4 + 2] * rhs.m[8 + col] + lhs.m[row * 4 + 3] * rhs.m[12 + col];
        }
    }

    return toReturn;
}

Vec4 operator * ( const Mat4 &lhs , const Vec4 &rhs )
{
    float x = lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z + lhs[3] * rhs.w ;
    float y = lhs[4] * rhs.x + lhs[5] * rhs.y + lhs[6] * rhs.z + lhs[7] * rhs.w ;
    float z = lhs[8] * rhs.x + lhs[9] * rhs.y + lhs[10] * rhs.z + lhs[11] * rhs.w ;

    //TODO: see if we can omit the last calculation since we may not need it
    float w = lhs[12] * rhs.x + lhs[13] * rhs.y + lhs[14] * rhs.z + lhs[15] * rhs.w ;

    return Vec4(x,y,z,w);
}


Mat4 Mat4::IDENTITY()
{
    return Mat4({1,0,0,0  ,0,1,0,0  ,0,0,1,0  ,0,0,0,1}) ;
}
