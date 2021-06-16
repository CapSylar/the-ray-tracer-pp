#include <Vec4.h>
#include "catch2/catch.hpp"
#include "Mat4.h"

TEST_CASE("Matrix Tests")
{
    SECTION("testing Mat4 construction" , "[Mat4]")
    {
        Mat4 x;
        Mat4 y;
        y.m[0] = 0 ;
        y.m[1] = 1 ;
        y.m[2] = 2 ;
        y.m[3] = 3 ;
        y.m[4] = 4 ;
        y.m[5] = 5 ;
        y.m[6] = 6 ;
        y.m[7] = 7 ;
        y.m[8] = 8 ;
        y.m[9] = 9 ;
        y.m[10] = 10 ;
        y.m[11] = 11 ;
        y.m[12] = 12 ;
        y.m[13] = 13 ;
        y.m[14] = 14 ;
        y.m[15] = 15 ;

        REQUIRE( x == Mat4({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}));
        REQUIRE( y == Mat4({0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}));
    }

    SECTION("MATRIX multiplication")
    {
        Mat4 x = {1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2};
        Mat4 y = {-2,1,2,3,3,2,1,-1,4,3,6,5,1,2,7,8};

        Mat4 z = x*y;

        REQUIRE(x*y == Mat4({20,22,50,48,44,54,114,108,40,58,110,102,16,26,46,42}));
    }


    SECTION("MATRIX * VECTOR multiplication")
    {
        Mat4 x = {1,2,3,4,2,4,4,2,8,6,4,1,0,0,0,1};
        Vec4 y(1,2,3,1);

        REQUIRE(x*y == Vec4(18,24,33,1));
    }


    SECTION("IDENTITY MATRIX TESTS")
    {
        Mat4 x = {1,0,0,0  ,0,1,0,0  ,0,0,1,0   ,0,0,0,1 };
        Mat4 ident = Mat4::IDENTITY();
        Mat4 z = {1,2,3,4,2,4,4,2,8,6,4,1,0,0,0,1};

        REQUIRE( x == ident );
        REQUIRE( z == z*ident);
    }

}
