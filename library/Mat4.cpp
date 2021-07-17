#include "Mat4.h"
#include "utilities.h"
#include "Transformation.h"
#include "Vec3f.h"
#include "Point3f.h"
#include "Ray.h"

bool operator == ( const Mat4 &lhs , const Mat4 &rhs )
{
    for ( int i = 0 ; i < 16 ; ++i )
    {
        if (!isEqualF(lhs.m[i], rhs.m[i]))
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

Point3f operator * ( const Mat4 &lhs , const Point3f &rhs )
{
    const auto  x = lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z + lhs[3] ;
    const auto  y = lhs[4] * rhs.x + lhs[5] * rhs.y + lhs[6] * rhs.z + lhs[7] ;
    const auto  z = lhs[8] * rhs.x + lhs[9] * rhs.y + lhs[10] * rhs.z + lhs[11] ;

    return Point3f(x,y,z);
}

Vec3f operator * ( const Mat4 &lhs , const Vec3f &rhs )
{
    const auto  x = lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z ;
    const auto  y = lhs[4] * rhs.x + lhs[5] * rhs.y + lhs[6] * rhs.z ;
    const auto  z = lhs[8] * rhs.x + lhs[9] * rhs.y + lhs[10] * rhs.z ;

    return Vec3f(x,y,z);
}

Vec3f Mat4::multByTranspose(const Vec3f &vec) const
{
    // better than computing the transpose and then multiplying with the vector that way
    // just access the matrix in a different way
    const auto  x = m[0] * vec.x + m[4] * vec.y + m[8] * vec.z ;
    const auto  y = m[1] * vec.x + m[5] * vec.y + m[9] * vec.z ;
    const auto  z = m[2] * vec.x + m[6] * vec.y + m[10] * vec.z ;

    return Vec3f(x,y,z);
}


std::ostream& operator<< ( std::ostream& os , const Mat4 &rhs )
{
    os << "[" << rhs[0] << " " << rhs[1] << " " << rhs[2] << " " << rhs[3] << "]\n";
    os << "[" << rhs[4] << " " << rhs[5] << " " << rhs[6] << " " << rhs[7] << "]\n";
    os << "[" << rhs[8] << " " << rhs[9] << " " << rhs[10] << " " << rhs[11] << "]\n";
    os << "[" << rhs[12] << " " << rhs[13] << " " << rhs[14] << " " << rhs[15] << "]";

    return os;
}




Mat4 Mat4::IDENTITY()
{
    return Mat4({1,0,0,0  ,0,1,0,0  ,0,0,1,0  ,0,0,0,1}) ;
}

Mat4 Mat4::view( Point3f from , Point3f to , Vec3f up )
{
    Vec3f forward = to - from ;
    forward.normalize();

    up.normalize();
    Vec3f left = cross( forward , up );
    Vec3f true_up = cross ( left , forward );

    Mat4 rotation_mat = { left.x , left.y , left.z , 0,
                          true_up.x , true_up.y , true_up.z , 0,
                          -forward.x , -forward.y , -forward.z , 0,
                          0,0,0,1 };

    return rotation_mat * getTranslation(-from.x,-from.y,-from.z);
    // could do the last multiplication manually, but this function is very rarely called, maybe once per program per render
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

Mat4 Mat4::transpose_copy() const {
    Mat4 temp;
    for ( int row = 0 ; row < 4 ; ++row )
    {
        for ( int col = 0 ; col < 4 ; ++col )
        {
            temp[col*4 + row] = m[row*4 + col];
        }
    }

    return temp;
}

Mat4& Mat4::transpose()
{
    *this = transpose_copy();
    return *this;
}

Mat4& Mat4::operator= ( Mat4 &&ref ) noexcept
{
    m = std::move(ref.m);
    return *this;
}

