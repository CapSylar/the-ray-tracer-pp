#include "Mat4.h"
#include "Vec4.h"
#include "utilities.h"
#include "Transformation.h"

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

Mat4 Mat4::invert_copy() const
{ // from MESA implementation

    Mat4 inv;
    float det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
             m[4]  * m[11] * m[14] +
             m[8]  * m[6]  * m[15] -
             m[8]  * m[7]  * m[14] -
             m[12] * m[6]  * m[11] +
             m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
              m[4]  * m[10] * m[13] +
              m[8]  * m[5] * m[14] -
              m[8]  * m[6] * m[13] -
              m[12] * m[5] * m[10] +
              m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
             m[1]  * m[11] * m[14] +
             m[9]  * m[2] * m[15] -
             m[9]  * m[3] * m[14] -
             m[13] * m[2] * m[11] +
             m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
             m[0]  * m[11] * m[13] +
             m[8]  * m[1] * m[15] -
             m[8]  * m[3] * m[13] -
             m[12] * m[1] * m[11] +
             m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
             m[0]  * m[7] * m[14] +
             m[4]  * m[2] * m[15] -
             m[4]  * m[3] * m[14] -
             m[12] * m[2] * m[7] +
             m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
              m[0]  * m[6] * m[13] +
              m[4]  * m[1] * m[14] -
              m[4]  * m[2] * m[13] -
              m[12] * m[1] * m[6] +
              m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
             m[1] * m[7] * m[10] +
             m[5] * m[2] * m[11] -
             m[5] * m[3] * m[10] -
             m[9] * m[2] * m[7] +
             m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
              m[0] * m[7] * m[9] +
              m[4] * m[1] * m[11] -
              m[4] * m[3] * m[9] -
              m[8] * m[1] * m[7] +
              m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    //TODO: assume all our matrices are invertible
//    if (det == 0)
//        return 1;

    det = 1.0f / det;

    for (i = 0; i < 16; i++)
        inv[i] = inv[i] * det;

    return inv;
}

//TODO: check if these can be done in a better way
Mat4& Mat4::invert()
{
    *this = invert_copy();
    return *this;
}

Mat4 &Mat4::rotate_x(float r)
{
    Mat4 x = getRotationX(r);
    *this = x * *this ; // reverse order is important
    return *this;
}

Mat4 &Mat4::rotate_y(float r)
{
    Mat4 y = getRotationY(r);
    *this = y * *this;
    return *this;
}

Mat4 &Mat4::rotate_z(float r)
{
    Mat4 z = getRotationZ(r);
    *this = z * *this;
    return *this;
}

Mat4 &Mat4::translate( float x , float y , float z )
{
    Mat4 trans = getTranslation(x,y,z);
    *this = trans * *this;
    return *this;
}

Mat4 &Mat4::scale(float x, float y, float z)
{
    Mat4 scale = getScaling(x,y,z);
    *this = scale * *this;
    return *this;
}

Mat4 &Mat4::shear(float Xy , float Xz , float Yx , float Yz , float Zx , float Zy)
{
    Mat4 shear = getShearing( Xy , Xz , Yx , Yz , Zx , Zy );
    *this = shear * *this;
    return *this;
}
