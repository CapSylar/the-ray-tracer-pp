#include "catch2/catch.hpp"
#include <iostream>
#include <vector>
#include "../src/Ray.h"
#include "Sphere.h"
#include "Intersection.h"

TEST_CASE("RAY TESTS")
{
    SECTION("testing ray creation")
    {
        Ray uut(Vec4::getPoint(1, 2, 3), Vec4::getVector(4, 5, 6));

        REQUIRE(uut.origin == Vec4::getPoint(1, 2, 3));
        REQUIRE(uut.direction == Vec4::getVector(4, 5, 6));
    }

    SECTION("computing a point from a distance")
    {
        Ray uut(Vec4::getPoint(2, 3, 4), Vec4::getVector(1, 0, 0));

        REQUIRE(uut.position(0) == Vec4::getPoint(2, 3, 4));
        REQUIRE(uut.position(1) == Vec4::getPoint(3, 3, 4));
        REQUIRE(uut.position(-1) == Vec4::getPoint(1, 3, 4));
        REQUIRE(uut.position(2.5) == Vec4::getPoint(4.5, 3, 4));
    }


    SECTION("a ray intersects a Sphere at two points")
    {
        Ray r(Vec4::getPoint(0, 0, -5), Vec4::getVector(0, 0, 1));
        Sphere s;
        auto list = s.intersect(r);

        REQUIRE(list.size() == 2);
        REQUIRE(list[0].t == 4);
        REQUIRE(list[1].t == 6);

    }

    SECTION("a ray intersects a Sphere at a tangent")
    {
        Ray r(Vec4::getPoint(0, 1, -5), Vec4::getVector(0, 0, 1));
        Sphere s;
        auto list = s.intersect(r);

        REQUIRE(list.size() == 2);
        REQUIRE(list[0].t == 5);
        REQUIRE(list[1].t == 5);
    }

    SECTION("the ray misses the sphere")
    {
        Ray r(Vec4::getPoint(0, 2, -5), Vec4::getVector(0, 0, 1));
        Sphere s;
        auto list = s.intersect(r);

        REQUIRE(list.empty());
    }

    SECTION("the ray originates from within the sphere")
    {
        Ray r(Vec4::getPoint(0, 0, 0), Vec4::getVector(0, 0, 1));
        Sphere s;
        auto list = s.intersect(r);

        REQUIRE(list.size() == 2);
        REQUIRE(list[0].t == -1);
        REQUIRE(list[1].t == 1);
    }


    SECTION("a sphere is behind a ra")
    {
        Ray r(Vec4::getPoint(0, 0, 5), Vec4::getVector(0, 0, 1));
        Sphere s;
        auto list = s.intersect(r);

        REQUIRE(list.size() == 2);
        REQUIRE(list[0].t == -6);
        REQUIRE(list[1].t == -4);
    }
}

TEST_CASE("testing the get_hit function")
{
    Sphere s;
    std::vector<Intersection> list;

    SECTION("testing the get_hit function")
    {
        auto s1 = Intersection( 1 , s );
        auto s2 = Intersection( 2 , s );
        list.push_back(s1);
        list.push_back(s2);

        auto ret = Intersection::get_hit(list);

        REQUIRE( ret == s1 );
    }


    SECTION("testing the hit function with some negative t")
    {
        auto s1 = Intersection( -1 , s );
        auto s2 = Intersection( 2 , s );
        list.push_back(s1);
        list.push_back(s2);

        auto ret = Intersection::get_hit(list);

        REQUIRE( ret == s2 );
    }

    SECTION("the hit, when all intersections are negative")
    {
        auto s1 = Intersection( -2 , s );
        auto s2 = Intersection( -1 , s );
        list.push_back(s1);
        list.push_back(s2);

        auto ret = Intersection::get_hit(list);

        REQUIRE(!ret.has_value());
    }

    SECTION("the hit, when all intersections are negative")
    {
        auto s1 = Intersection( -2 , s );
        auto s2 = Intersection( -1 , s );
        list.push_back(s1);
        list.push_back(s2);

        auto ret = Intersection::get_hit(list);

        REQUIRE(!ret.has_value());
    }

    SECTION("the hit, when all intersections are negative")
    {
        auto s1 = Intersection( -3 , s );
        auto s2 = Intersection( 2 , s );
        auto s3 = Intersection( 5 , s );
        auto s4 = Intersection( 7 , s );

        list.push_back(s1);
        list.push_back(s2);
        list.push_back(s3);
        list.push_back(s4);

        auto ret = Intersection::get_hit(list);

        REQUIRE( ret == s2 );
    }
}


TEST_CASE("transforming rays")
{
    Ray ray( Vec4::getPoint(1,2,3) , Vec4::getVector(0,1,0));
    Mat4 x;

    SECTION("translating a ray")
    {
        x.translate(3,4,5);
        ray.transform(x);

        REQUIRE(ray.origin == Vec4::getPoint(4,6,8));
        REQUIRE(ray.direction == Vec4::getVector(0,1,0));
    }

    SECTION("scaling a ray")
    {
        x.scale(2,3,4);
        ray.transform(x);

        REQUIRE(ray.origin == Vec4::getPoint(2,6,12));
        REQUIRE(ray.direction == Vec4::getVector(0,3,0));
    }
}