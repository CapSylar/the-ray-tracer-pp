#include "catch2/catch.hpp"
#include "Triangle.h"
#include "Ray.h"
#include <vector>
#include "Intersection.h"

TEST_CASE("triangle tests")
{
    Triangle t(nullptr, Point3f(0,1,0) , Point3f(-1,0,0) , Point3f(1,0,0));
    std::vector<Intersection> list;

    SECTION("testing triangle creation")
    {
        REQUIRE(t.e1 == Vec3f(-1,-1,0));
        REQUIRE(t.e2 == Vec3f(1,-1,0));
        REQUIRE(t._n1 == Vec3f(0,0,1));
    }

    SECTION("finding the normal on a triangle")
    {
        REQUIRE(t.local_normal_at(Point3f(0,0.5f,0)) == t._n1);
        REQUIRE(t.local_normal_at(Point3f(-0.5f,0.75f,0)) == t._n1);
        REQUIRE(t.local_normal_at(Point3f(0.5f,0.25f,0)) == t._n1);
    }

    SECTION("intersecting a ray parallel to the triangle")
    {
        Ray ray ( Point3f(0,-1,-2) , Vec3f(0,1,0));
        t.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("a ray misses the p1-p3 edge")
    {
        Ray ray ( Point3f(1,1,-2) , Vec3f(0,0,1));
        t.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("a ray misses the p1-p2 edge")
    {
        Ray ray ( Point3f(-1,1,-2) , Vec3f(0,0,1));
        t.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("a ray misses the p2-p3 edge")
    {
        Ray ray ( Point3f(0,-1,-2) , Vec3f(0,0,1));
        t.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("a ray strikes a triangle")
    {
        Ray ray ( Point3f(0,0.5f,-2) , Vec3f(0,0,1));
        t.local_intersect( ray , list );

        REQUIRE( list.size() == 1 );
        REQUIRE( list[0].t == 2 );
    }
}

TEST_CASE("testing smooth triangles")
{
    Triangle t(nullptr, Point3f(0,1,0) , Point3f(-1,0,0) , Point3f(1,0,0) ,
               Vec3f(0,1,0) , Vec3f(-1,0,0) , Vec3f(1,0,0));

    std::vector<Intersection> list;

    SECTION("an intersection can evaluate u and v")
    {
        Ray ray( Point3f(-0.2f,0.3f,-2) , Vec3f(0,0,1) );
        t.local_intersect( ray , list );
        REQUIRE( !list.empty() );
        REQUIRE( list[0]._u == 0.45f);
        REQUIRE( list[0]._v == 0.25f);
    }

//    SECTION("a smooth triangle uses u and v to interpolate the normal")
//    {
//        Intersection xx ( 1 , &t , 0.45f , 0.25f );
//        const auto normal = t.local_normal_at( Point3f( 0.45f , 0.25f , 0 ) );
//
//        REQUIRE( normal == Vec3f( -0.5547f , 0.83205f , 0  ) );
//    }

}