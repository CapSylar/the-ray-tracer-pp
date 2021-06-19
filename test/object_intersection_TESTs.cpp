#include "catch2/catch.hpp"

#include "Sphere.h"
#include "Mat4.h"
#include "Intersection.h"

TEST_CASE("Sphere intersection tests")
{
    Sphere s;
    Ray ray( Vec4::getPoint(0,0,-5) , Vec4::getVector(0,0,1));

    SECTION("test sphere default transformation")
    {
        REQUIRE( s.transform == Mat4::IDENTITY() );
    }

    SECTION("intersecting a scaled sphere with a ray")
    {
        s.transform.scale(2,2,2);
        auto list = s.intersect(ray);

        REQUIRE(list.size() == 2);
        REQUIRE(list[0].t == 3);
        REQUIRE(list[1].t == 7);
    }

    SECTION("intersecting a translated sphere with a ray")
    {
        s.transform.scale(5,0,0 );
        auto list = s.intersect(ray);

        REQUIRE(list.empty());
    }





}