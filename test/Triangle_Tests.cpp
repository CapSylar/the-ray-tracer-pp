#include "catch2/catch.hpp"
#include "Triangle.h"
#include "Ray.h"
#include <vector>
#include "Intersection.h"

TEST_CASE("triangle tests")
{
    Triangle t(nullptr, Vec4::getPoint(0,1,0) , Vec4::getPoint(-1,0,0) , Vec4::getPoint(1,0,0));
    std::vector<Intersection> list;

    SECTION("testing triangle creation")
    {
        REQUIRE(t.e1 == Vec4::getVector(-1,-1,0));
        REQUIRE(t.e2 == Vec4::getVector(1,-1,0));
        REQUIRE(t.normal == Vec4::getVector(0,0,-1));
    }

    SECTION("finding the normal on a triangle")
    {
        REQUIRE(t.local_normal_at(Vec4::getPoint(0,0.5f,0)) == t.normal);
        REQUIRE(t.local_normal_at(Vec4::getPoint(-0.5f,0.75f,0)) == t.normal);
        REQUIRE(t.local_normal_at(Vec4::getPoint(0.5f,0.25f,0)) == t.normal);
    }

    SECTION("intersecting a ray parallel to the triangle")
    {
        Ray ray ( Vec4::getPoint(0,-1,-2) , Vec4::getVector(0,1,0));
        t.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("a ray misses the p1-p3 edge")
    {
        Ray ray ( Vec4::getPoint(1,1,-2) , Vec4::getVector(0,0,1));
        t.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("a ray misses the p1-p2 edge")
    {
        Ray ray ( Vec4::getPoint(-1,1,-2) , Vec4::getVector(0,0,1));
        t.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("a ray misses the p2-p3 edge")
    {
        Ray ray ( Vec4::getPoint(0,-1,-2) , Vec4::getVector(0,0,1));
        t.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("a ray strikes a triangle")
    {
        Ray ray ( Vec4::getPoint(0,0.5f,-2) , Vec4::getVector(0,0,1));
        t.local_intersect( ray , list );

        REQUIRE( list.size() == 1 );
        REQUIRE( list[0].t == 2 );
    }
}