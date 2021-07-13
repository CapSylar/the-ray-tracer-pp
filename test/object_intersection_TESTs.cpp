#include "catch2/catch.hpp"

#include "Sphere.h"
#include "Mat4.h"
#include "Intersection.h"
#include "Plane.h"
#include "Vec3f.h"
#include "Point3f.h"
#include "Ray.h"
#include "PlainMaterial.h"

TEST_CASE("Sphere intersection tests")
{
    Ray ray( Point3f(0,0,-5) , Vec3f(0,0,1));
    std::vector<Intersection> list;

    SECTION("test sphere default transformation")
    {
        Sphere s ( new PlainMaterial() );
        REQUIRE(s.inverse_trans == Mat4::IDENTITY() );
    }

    SECTION("intersecting a scaled sphere with a ray")
    {
        Sphere s( ( new PlainMaterial() ) , Mat4::IDENTITY().scale(2,2,2));
        s.intersect(ray , list );

        REQUIRE(list.size() == 2);
        REQUIRE(list[0].t == 3);
        REQUIRE(list[1].t == 7);
    }

//    SECTION("intersecting a translated sphere with a ray")
//    {
//        Sphere s ( new PlainMaterial() ,  Mat4::IDENTITY().scale(5,1,1)) ;
//        s.intersect(ray , list );
//
//        REQUIRE(list.empty());
//    }
}

TEST_CASE("Plane Tests")
{
    Plane plane ( new PlainMaterial() );
    SECTION("Plane creation test")
    {
        REQUIRE(plane.inverse_trans == Mat4::IDENTITY() );
    }

    SECTION("testing Plane normals")
    {
        REQUIRE( plane.normal_at(Point3f(0,0,0)) == Vec3f(0,1,0) ) ;
        REQUIRE( plane.normal_at(Point3f(10,0,0)) == Vec3f(0,1,0) ) ;
        REQUIRE( plane.normal_at(Point3f(100,0,-20)) == Vec3f(0,1,0) ) ;
    }


    SECTION( "Intersect with a ray parallel to the plane" )
    {
        Ray ray ( Point3f(0,10,0) , Vec3f(0,0,1)) ;
        std::vector<Intersection> list ;
        plane.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION( "Intersect with a coplanar ray" )
    {
        Ray ray ( Point3f(0,0,0) , Vec3f(0,0,1)) ;
        std::vector<Intersection> list ;
        plane.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }


    SECTION( "A ray intersecting a plane from above" )
    {
        Ray ray ( Point3f(0,1,0) , Vec3f(0,-1,0)) ;
        std::vector<Intersection> list ;
        plane.local_intersect( ray , list );

        REQUIRE( list.size() == 1 );
        REQUIRE( list[0].t == 1 ) ;
        REQUIRE( list[0].obj == &plane );
    }

    SECTION( "A ray intersecting a plane from below" )
    {
        Ray ray ( Point3f(0,-1,0) , Vec3f(0,1,0)) ;
        std::vector<Intersection> list ;
        plane.local_intersect( ray , list );

        REQUIRE( list.size() == 1 );
        REQUIRE( list[0].t == 1 ) ;
        REQUIRE( list[0].obj == &plane );
    }

}