#include <unordered_map>
#include "catch2/catch.hpp"
#include "Vec4.h"
#include "Mat4.h"
#include "Transformation.h"

TEST_CASE("Translation Tests")
{
    Point p = Vec4::getPoint(-3,4,5);
    Mat4 trans = getTranslation(5,-3,2);

    SECTION("translation matrix tests")
    {
        Point result = Vec4::getPoint(2,1,7);
        REQUIRE(trans * p == result );
    }

    SECTION("inverse translation matrix tests")
    {
        Point result = Vec4::getPoint(-8,7,3);
        REQUIRE(trans.invert() * p == result );
    }

    SECTION("translation matrices should not affect vectors")
    {
        Vector v = Vec4::getVector(-3,4,5);
        REQUIRE(trans*v == v);
    }
}


TEST_CASE("Scaling Tests")
{
    Mat4 scaling = getScaling(2,3,4);
    Point p = Vec4::getPoint(-4,6,8);
    Vector v = Vec4::getVector(-4,6,8);

    SECTION("scaling a point")
    {
        Point res = Vec4::getPoint(-8,18,32);
        REQUIRE(scaling * p == res );
    }

    SECTION("scaling a vector")
    {
        Point res = Vec4::getVector(-8,18,32);
        REQUIRE( scaling * v == res );
    }

    SECTION("multiplying by inverse of the scaling matrix")
    {
        Mat4 inverse = scaling.invert_copy();
        Vector res = Vec4::getVector(-2,2,2);
        REQUIRE( inverse * v == res );
    }

    SECTION("scaling by a negative value")
    {
        Mat4 scaling = getScaling(-1,1,1);
        Point p = Vec4::getPoint(2,3,4);
        REQUIRE(scaling * p == Vec4::getPoint(-2,3,4));
    }

}


TEST_CASE("Rotations around X tests")
{
    Point p = Vec4::getPoint(0,1,0);

    // x rotations

    Mat4 half_x = getRotationX( M_PI/4 );
    Mat4 full_x = getRotationX( M_PI/2 );

    float sqrt2over2 = sqrtf(2)/2;

    SECTION("testing rotation around X")
    {
        REQUIRE(half_x * p == Vec4::getPoint(0,sqrt2over2,sqrt2over2));
        REQUIRE(full_x * p == Vec4::getPoint(0,0,1));
    }

    SECTION("inverse of rotation around x")
    {
        REQUIRE(half_x.invert() * p == Vec4::getPoint(0,sqrt2over2,-sqrt2over2));
    }
}

TEST_CASE("Rotations around Y tests")
{
    Point p = Vec4::getPoint(0,0,1);
    // y rotations

    Mat4 half_y = getRotationY( M_PI/4 );
    Mat4 full_y = getRotationY( M_PI/2 );

    float sqrt2over2 = sqrtf(2)/2;

    SECTION("testing rotation around Y")
    {
        REQUIRE(half_y * p == Vec4::getPoint(sqrt2over2,0,sqrt2over2));
        REQUIRE(full_y * p == Vec4::getPoint(1,0,0));
    }

}

TEST_CASE("Rotations around Z tests")
{
    Point p = Vec4::getPoint(0,1,0);
    // z rotations

    Mat4 half_z = getRotationZ( M_PI/4 );
    Mat4 full_z = getRotationZ( M_PI/2 );

    float sqrt2over2 = sqrtf(2)/2;

    SECTION("testing rotation around Z")
    {
        REQUIRE(half_z * p == Vec4::getPoint(-sqrt2over2,sqrt2over2,0));
        REQUIRE(full_z * p == Vec4::getPoint(-1,0,0));
    }
}

TEST_CASE("Testing shearing transformation")
{
    Point p = Vec4::getPoint(2,3,4);

    SECTION("move x in prop to y")
    {
        Mat4 trans = getShearing(1,0,0,0,0,0);
        REQUIRE(trans * p == Vec4::getPoint(5,3,4));
    }

    SECTION("move x in prop to z")
    {
        Mat4 trans = getShearing(0,1,0,0,0,0);
        REQUIRE(trans * p == Vec4::getPoint(6,3,4));
    }

    SECTION("move y in prop to x")
    {
        Mat4 trans = getShearing(0,0,1,0,0,0);
        REQUIRE(trans * p == Vec4::getPoint(2,5,4));
    }

    SECTION("move y in prop to z")
    {
        Mat4 trans = getShearing(0,0,0,1,0,0);
        REQUIRE(trans * p == Vec4::getPoint(2,7,4));
    }

    SECTION("move z in prop to x")
    {
        Mat4 trans = getShearing(0,0,0,0,1,0);
        REQUIRE(trans * p == Vec4::getPoint(2,3,6));
    }

    SECTION("move z in prop to y")
    {
        Mat4 trans = getShearing(0,0,0,0,0,1);
        REQUIRE(trans * p == Vec4::getPoint(2,3,7));
    }
}

TEST_CASE("chaining transformation tests")
{
    SECTION("test chaining transformations")
    {
        Mat4 start = Mat4::IDENTITY();
        start.rotate_x(M_PI/2).scale(5,5,5).translate(10,5,7);
        Point p = Vec4::getPoint(1,0,1);
        REQUIRE( start * p == Vec4::getPoint(15,0,7));
    }
}
