#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "Vec4.h"

TEST_CASE("building Vec4 correctly" , "[Vec4]")
{
    SECTION("testing default constructed Vec4")
    {
        Point x;

        REQUIRE(x.x == 0);
        REQUIRE(x.y == 0);
        REQUIRE(x.z == 0);
        REQUIRE(x.w == 0);
    }

    SECTION("testing getPoint created")
    {
        Point x = Vec4::getPoint(2, 3, 4);

        REQUIRE(x.x == 2 );
        REQUIRE(x.y == 3 );
        REQUIRE(x.z == 4 );
        REQUIRE(x.w == 1 );
    }

    SECTION("testing getVector created")
    {
        Point x = Vec4::getVector(2, 3, 4);

        REQUIRE(x.x == 2 );
        REQUIRE(x.y == 3 );
        REQUIRE(x.z == 4 );
        REQUIRE(x.w == 0 );
    }
}

TEST_CASE("testing compare operators" , "[Vec4]")
{
    SECTION("testing compare operator with points")
    {
        Point x = Vec4::getPoint(2, 3, 4);
        Point y = Vec4::getPoint(2,3,4);

        REQUIRE(x==y);
    }

    SECTION("testing compare operator with vectors")
    {
        Point x = Vec4::getVector(2, 6, 10);
        Point y = Vec4::getVector(2,6,10);

        REQUIRE(x==y);
    }

    SECTION("testing compare operator false")
    {
        Point x = Vec4::getPoint(2, 4, 4);
        Point y = Vec4::getPoint(2,3,4);

        REQUIRE(x!=y);
    }

    SECTION("testing compare operator false")
    {
        Point x = Vec4::getPoint(2, 4, 4);
        Point y = Vec4::getPoint(2,3,4);

        REQUIRE(x!=y);
    }
}

TEST_CASE("testing Vec4 arithmetic operators" , "[Vec4]")
{
    Point x = Vec4::getPoint(1,2,3);
    Point a = Vec4::getPoint( 3, 4 ,5 );
    Vector y = Vec4::getVector(3,4,5);
    Vector z = Vec4::getVector(6,7,8);

    SECTION("testing +- operators between points and vectors")
    {
        REQUIRE(x+y == Vec4::getPoint(4,6,8));
        REQUIRE(x-y == Vec4::getPoint(-2,-2,-2));
    }

    SECTION("testing +- operators between vectors")
    {
        REQUIRE(y+z == Vec4::getVector(9,11,13));
        REQUIRE(y-z == Vec4::getVector(-3,-3,-3));
    }

    SECTION("testing +- operators between points")
    {
        REQUIRE(x-a == Vec4::getVector(-2,-2,-2));
        REQUIRE(a-x == Vec4::getVector(2,2,2));
    }

    SECTION("testing the negation operator")
    {
        REQUIRE(-y == Vec4::getVector(-3,-4,-5));
        REQUIRE(-z == Vec4::getVector(-6,-7,-8));
    }

    SECTION("testing the */ operator")
    {
        REQUIRE(z*2 == Vec4::getVector(12,14,16));
        REQUIRE(z*10 == Vec4::getVector(60,70,80));
        REQUIRE(z*0.5 == Vec4::getVector(3,3.5,4));

        REQUIRE(z/2 == Vec4::getVector(3,3.5,4));
        REQUIRE(z/4 == Vec4::getVector(1.5,1.75,2));
    }
}

TEST_CASE("testing Vec4 mag,normalization,dot and cross products" , "[Vec4]")
{

    SECTION ( "testing magnitude() function")
    {
        Vector x = Vec4::getVector(1,0,0);
        Vector y = Vec4::getVector(0,1,0);
        Vector z = Vec4::getVector(0,0,1);

        Vector a = Vec4::getVector(1,2,3);
        Vector b = Vec4::getVector(-1,-2,-3);

        REQUIRE(x.magnitude() == 1);
        REQUIRE(y.magnitude() == 1);
        REQUIRE(z.magnitude() == 1);
        REQUIRE(a.magnitude() == sqrtf(14));
        REQUIRE(b.magnitude() == sqrtf(14));
    }

    SECTION ( "testing normalizing vector")
    {
        REQUIRE(Vec4::getVector(4,0,0).normalize() == Vec4::getVector(1,0,0));
        float sqrt14 = sqrtf(14);
        REQUIRE(Vec4::getVector(1,2,3).normalize() == Vec4::getVector(1/sqrt14,
                                                                      2/sqrt14,
                                                                      3/sqrt14));


    }

    SECTION ( "testing dot product")
    {
        Vector x = Vec4::getVector(1,2,3);
        Vector y = Vec4::getVector(2,3,4);

        REQUIRE( x * y == 20 );
    }

    SECTION ( "testing cross product")
    {
        Vector x = Vec4::getVector(1,2,3);
        Vector y = Vec4::getVector(2,3,4);

        REQUIRE( Vec4::cross(x,y) == Vec4::getVector(-1,2,-1) );
    }







}
