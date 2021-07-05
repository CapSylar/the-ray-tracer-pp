#ifndef RAY_TRACER_MAT4_H
#define RAY_TRACER_MAT4_H

#include "Vec4.h"

#include <memory>
#include <vector>

class Mat4
{
public:
    std::vector<float> m;

    static Mat4 IDENTITY();
    static Mat4 view( Point from , Point to , Vector up );

    Mat4() : m({1,0,0,0  ,0,1,0,0  ,0,0,1,0  ,0,0,0,1}) {} // TODO: join this and IDENTITY()
    Mat4( std::initializer_list<float> il ) : m( il.begin() , il.end() ) {}

    Mat4 ( const Mat4 &ref ): m(ref.m) {} 

    Mat4& operator = ( Mat4 &ref ) = default;

    Mat4( Mat4 &&ref ) noexcept : m(std::move(ref.m)) {}

    Mat4& operator = ( Mat4 &&ref ) noexcept ;

    float& operator[] ( int index )
    {
        return m[index];
    }

    const float& operator[] ( int index ) const
    {
        return m[index];
    }

    Mat4& transpose() ;
    Mat4 transpose_copy() const;

    Mat4& rotate_x( float r );
    Mat4& rotate_y( float r);
    Mat4& rotate_z( float r);
    Mat4& translate( float x , float y , float z);
    Mat4& scale( float x , float y , float z );
    Mat4& shear( float Xy , float Xz , float Yx , float Yz , float Zx , float Zy );

    Mat4& invert() ;
    Mat4 invert_copy () const;
};

bool operator == ( const Mat4 &lhs , const Mat4 &rhs );
Mat4 operator * ( const Mat4 &lhs , const Mat4 &rhs );
Vec4 operator * ( const Mat4 &lhs , const Vec4 &rhs );
std::ostream& operator<< ( std::ostream& os , const Mat4 &rhs );

#endif //RAY_TRACER_MAT4_H
