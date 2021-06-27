#include "catch2/catch.hpp"

#include "Sphere.h"
#include "Mat4.h"
#include "Intersection.h"
#include "Plane.h"

TEST_CASE("Sphere intersection tests")
{
    Sphere s;
    Ray ray( Vec4::getPoint(0,0,-5) , Vec4::getVector(0,0,1));
    std::vector<Intersection> list;

    SECTION("test sphere default transformation")
    {
        REQUIRE( s.transform == Mat4::IDENTITY() );
    }

    SECTION("intersecting a scaled sphere with a ray")
    {
        s.transform.scale(2,2,2);
        s.intersect(ray , list );

        REQUIRE(list.size() == 2);
        REQUIRE(list[0].t == 3);
        REQUIRE(list[1].t == 7);
    }

    SECTION("intersecting a translated sphere with a ray")
    {
        s.transform.scale(5,0,0 );
        s.intersect(ray , list );

        REQUIRE(list.empty());
    }
}

TEST_CASE("Plane Tests")
{
    SECTION("Plane creation test")
    {
        Plane plane;
        REQUIRE( plane.transform == Mat4::IDENTITY() );
        REQUIRE( plane.material == Material() );
    }

    SECTION("testing Plane normals")
    {
        Plane plane;
        REQUIRE( plane.normal_at(Vec4::getPoint(0,0,0)) == Vec4::getVector(0,1,0) ) ;
        REQUIRE( plane.normal_at(Vec4::getPoint(10,0,0)) == Vec4::getVector(0,1,0) ) ;
        REQUIRE( plane.normal_at(Vec4::getPoint(100,0,-20)) == Vec4::getVector(0,1,0) ) ;
    }


    SECTION( "Intersect with a ray parallel to the plane" )
    {
        Plane plane;
        Ray ray ( Vec4::getPoint(0,10,0) , Vec4::getVector(0,0,1)) ;
        std::vector<Intersection> list ;
        plane.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION( "Intersect with a coplanar ray" )
    {
        Plane plane;
        Ray ray ( Vec4::getPoint(0,0,0) , Vec4::getVector(0,0,1)) ;
        std::vector<Intersection> list ;
        plane.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }


    SECTION( "A ray intersecting a plane from above" )
    {
        Plane plane;
        Ray ray ( Vec4::getPoint(0,1,0) , Vec4::getVector(0,-1,0)) ;
        std::vector<Intersection> list ;
        plane.local_intersect( ray , list );

        REQUIRE( list.size() == 1 );
        REQUIRE( list[0].t == 1 ) ;
        REQUIRE( list[0].obj == &plane );
    }

    SECTION( "A ray intersecting a plane from below" )
    {
        Plane plane;
        Ray ray ( Vec4::getPoint(0,-1,0) , Vec4::getVector(0,1,0)) ;
        std::vector<Intersection> list ;
        plane.local_intersect( ray , list );

        REQUIRE( list.size() == 1 );
        REQUIRE( list[0].t == 1 ) ;
        REQUIRE( list[0].obj == &plane );
    }





}