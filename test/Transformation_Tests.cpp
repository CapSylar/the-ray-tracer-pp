#include <unordered_map>
#include "catch2/catch.hpp"
#include "Mat4.h"
#include "Transformation.h"

#include "Vec3f.h"
#include "Point3f.h"

TEST_CASE("Translation Tests")
{
    Point3f p (-3,4,5);
    Mat4 trans = getTranslation(5,-3,2);

    SECTION("translation matrix tests")
    {
        Point3f result(2,1,7);
        REQUIRE(trans * p == result );
    }

    SECTION("inverse translation matrix tests")
    {
        Point3f result (-8,7,3);
        REQUIRE(trans.invert() * p == result );
    }

    SECTION("translation matrices should not affect vectors")
    {
        Vec3f v (-3,4,5);
        REQUIRE(trans*v == v);
    }
}


TEST_CASE("Scaling Tests")
{
    Mat4 scaling = getScaling(2,3,4);
    Point3f p (-4,6,8);
    Vec3f v (-4,6,8);

    SECTION("scaling a point")
    {
        Point3f res(-8,18,32);
        REQUIRE(scaling * p == res );
    }

    SECTION("scaling a vector")
    {
        Vec3f res (-8,18,32);
        REQUIRE( scaling * v == res );
    }

    SECTION("multiplying by inverse of the scaling matrix")
    {
        Mat4 inverse = scaling.invert_copy();
        Vec3f res (-2,2,2);
        REQUIRE( inverse * v == res );
    }

    SECTION("scaling by a negative value")
    {
        Mat4 scaling = getScaling(-1,1,1);
        Point3f p (2,3,4);
        REQUIRE(scaling * p == Point3f(-2,3,4));
    }

}


TEST_CASE("Rotations around X tests")
{
    Point3f p (0,1,0);

    // x rotations

    Mat4 half_x = getRotationX( M_PI/4 );
    Mat4 full_x = getRotationX( M_PI/2 );

    float sqrt2over2 = sqrtf(2)/2;

    SECTION("testing rotation around X")
    {
        REQUIRE(half_x * p == Point3f(0,sqrt2over2,sqrt2over2));
        REQUIRE(full_x * p == Point3f(0,0,1));
    }

    SECTION("inverse of rotation around x")
    {
        REQUIRE(half_x.invert() * p == Point3f(0,sqrt2over2,-sqrt2over2));
    }
}

TEST_CASE("Rotations around Y tests")
{
    Point3f p (0,0,1);
    // y rotations

    Mat4 half_y = getRotationY( M_PI/4 );
    Mat4 full_y = getRotationY( M_PI/2 );

    float sqrt2over2 = sqrtf(2)/2;

    SECTION("testing rotation around Y")
    {
        REQUIRE(half_y * p == Point3f(sqrt2over2,0,sqrt2over2));
        REQUIRE(full_y * p == Point3f(1,0,0));
    }

}

TEST_CASE("Rotations around Z tests")
{
    Point3f p (0,1,0);
    // z rotations

    Mat4 half_z = getRotationZ( M_PI/4 );
    Mat4 full_z = getRotationZ( M_PI/2 );

    float sqrt2over2 = sqrtf(2)/2;

    SECTION("testing rotation around Z")
    {
        REQUIRE(half_z * p == Point3f(-sqrt2over2,sqrt2over2,0));
        REQUIRE(full_z * p == Point3f(-1,0,0));
    }
}

TEST_CASE("Testing shearing transformation")
{
    Point3f p (2,3,4);

    SECTION("move x in prop to y")
    {
        Mat4 trans = getShearing(1,0,0,0,0,0);
        REQUIRE(trans * p == Point3f(5,3,4));
    }

    SECTION("move x in prop to z")
    {
        Mat4 trans = getShearing(0,1,0,0,0,0);
        REQUIRE(trans * p == Point3f(6,3,4));
    }

    SECTION("move y in prop to x")
    {
        Mat4 trans = getShearing(0,0,1,0,0,0);
        REQUIRE(trans * p == Point3f(2,5,4));
    }

    SECTION("move y in prop to z")
    {
        Mat4 trans = getShearing(0,0,0,1,0,0);
        REQUIRE(trans * p == Point3f(2,7,4));
    }

    SECTION("move z in prop to x")
    {
        Mat4 trans = getShearing(0,0,0,0,1,0);
        REQUIRE(trans * p == Point3f(2,3,6));
    }

    SECTION("move z in prop to y")
    {
        Mat4 trans = getShearing(0,0,0,0,0,1);
        REQUIRE(trans * p == Point3f(2,3,7));
    }
}

TEST_CASE("chaining transformation tests")
{
    SECTION("test chaining transformations")
    {
        Mat4 start = Mat4::IDENTITY();
        start.rotate_x(M_PI/2).scale(5,5,5).translate(10,5,7);
        Point3f p (1,0,1);
        REQUIRE( start * p == Point3f(15,0,7));
    }
}
