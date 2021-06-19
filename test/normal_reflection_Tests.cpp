#include "catch2/catch.hpp"
#include "Sphere.h"
#include "Ray.h"

TEST_CASE("normal tests")
{
    Sphere s;
    SECTION("the normal on a sphere at a point on the x axis")
    {
        auto test = s.normal_at(Vec4::getPoint(1,0,0));
        REQUIRE( test == Vec4::getVector(1,0,0) ) ;
    }

    SECTION("the normal on a sphere at a point on the y axis")
    {
        auto test = s.normal_at(Vec4::getPoint(0,1,0));
        REQUIRE( test == Vec4::getVector(0,1,0) ) ;
    }

    SECTION("the normal on a sphere at a point on the z axis")
    {
        auto test = s.normal_at(Vec4::getPoint(0,0,1));
        REQUIRE( test == Vec4::getVector(0,0,1) ) ;
    }

    SECTION("the normal of a sphere on a nonaxial point")
    {
        float sqrt3over3 = sqrtf(3)/3;
        auto test = s.normal_at(Vec4::getPoint(sqrt3over3,sqrt3over3,sqrt3over3));
        REQUIRE( test == Vec4::getVector(sqrt3over3,sqrt3over3,sqrt3over3) ) ;
    }

    SECTION("computed normal on a translated sphere")
    {
        s.transform.translate(0,1,0);
        auto n = s.normal_at( Vec4::getPoint(0,1.70711,-0.70711));
        REQUIRE( n == Vec4::getVector(0,0.707107,-0.707107));
    }

    SECTION("computed normal on a transformed sphere")
    {
        s.transform.rotate_z(M_PI/5).scale(1,0.5,1);
        auto n = s.normal_at( Vec4::getPoint(0, sqrtf(2)/2,-sqrtf(2)/2));
        REQUIRE( n == Vec4::getVector(0,0.970143,-0.242536));
    }
}

TEST_CASE("testing reflection of vectors")
{
    SECTION("reflecting a vector approaching at 45")
    {
        Vector v = Vec4::getVector(1,-1,0);
        Vector n = Vec4::getVector(0,1,0);
        auto r = Ray::reflect( v , n );
        REQUIRE( r == Vec4::getVector(1,1,0));
    }

    SECTION("reflecting a vector off a slanted surface")
    {
        Vector v = Vec4::getVector(0,-1,0);
        Vector n = Vec4::getVector(sqrtf(2)/2, sqrtf(2)/2,0);
        auto r = Ray::reflect( v , n );
        REQUIRE( r == Vec4::getVector(1,0,0));
    }
}