#ifndef RAY_TRACER_MAT4_H
#define RAY_TRACER_MAT4_H

#include "Vec4.h"

#include <memory>
#include <vector>

class Mat4
{
public:
    std::vector<float> m;

    Mat4() : m(16,0) {}
    Mat4( std::initializer_list<float> il ) : m( il.begin() , il.end() ) {}

    float operator[] ( int index ) const
    {
        return m[index];
    }

    static Mat4 IDENTITY();
};

bool operator == ( const Mat4 &lhs , const Mat4 &rhs );
Mat4 operator * ( const Mat4 &lhs , const Mat4 &rhs );
Vec4 operator * ( const Mat4 &lhs , const Vec4 &rhs );


#endif //RAY_TRACER_MAT4_H
