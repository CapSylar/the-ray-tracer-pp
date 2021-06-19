#include "catch2/catch.hpp"
#include "Mat4.h"
#include "Vec4.h"


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

        REQUIRE( x == Mat4({1,0,0,0  ,0,1,0,0  ,0,0,1,0  ,0,0,0,1}));
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

    SECTION("transposing matrices tests")
    {
        Mat4 x = {0,9,3,0,9,8,0,8,1,8,5,3,0,0,5,8};
        Mat4 x_transposed = {0,9,1,0,9,8,8,0,3,0,5,5,0,8,3,8};

        REQUIRE(x.transpose() == x_transposed);
    }


    SECTION("testing matrix inversion")
    {
        Mat4 x = {8,-5,9,2,  7,5,6,1,  -6,0,9,6,  -3,0,-9,-4};

        Mat4 x_inverted = {-0.15384616,-0.15384616,-0.282051295,-0.538461566,
                           -0.0769230798,0.123076923,0.025641026,0.0307692308,
                           0.358974367,0.358974367,0.43589744,0.923076928,
                           -0.692307711,-0.692307711,-0.769230783,-1.92307699};

        Mat4 y = {9,3,0,9,  -5,-2,-6,-3,   -4,9,6,4,  -7,6,6,2};

        Mat4 y_inverted = {-0.0407407433,-0.0777777806,0.144444451,-0.222222239,
                           -0.0777777806,0.0333333351,0.366666675,-0.333333343,
                           -0.0290123466,-0.146296307,-0.109259263,0.129629642,
                           0.177777782,0.0666666701,-0.266666681,0.333333343};

        REQUIRE(x.invert() == x_inverted);
        REQUIRE(y.invert() == y_inverted);
    }

    SECTION ("some more tests")
    {
        Mat4 a = {3,-9,7,3,  3,-8,2,-9,  -4,4,4,1,  -6,5,-1,1};
        Mat4 b = {8,2,2,2,  3,-1,7,0,   7,0,5,4,   6,-2,0,5 };

        Mat4 c = a*b;
        Mat4 d = c*b.invert();

        REQUIRE(a == d);
    }


}
