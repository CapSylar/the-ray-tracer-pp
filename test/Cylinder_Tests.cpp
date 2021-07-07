#include "catch2/catch.hpp"
#include "Cylinder.h"
#include "Ray.h"
#include <vector>
#include "Intersection.h"
#include "utilities.h"
#include "PlainMaterial.h"

TEST_CASE("testing cylinder")
{
    Cylinder c ( new PlainMaterial() );
    std::vector<Intersection> list;

    SECTION("a ray misses a cylinder 1")
    {
        Ray ray ( Vec4::getPoint(1,0,0) , Vec4::getVector(0,1,0) );
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("a ray misses a cylinder 2")
    {
        Ray ray ( Vec4::getPoint(0,0,0) , Vec4::getVector(0,1,0) );
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }


    SECTION("a ray misses a cylinder 3")
    {
        Ray ray ( Vec4::getPoint(0,0,-5) , Vec4::getVector(1,1,1) );
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }
}

TEST_CASE("the ray hits the cylinder")
{
    Cylinder c ( new PlainMaterial() );
    std::vector<Intersection> list;

    SECTION("a ray strikes the cylinder scenario 1")
    {
        Ray ray ( Vec4::getPoint(1,0,-5) , Vec4::getVector(0,0,1).normalize() );
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
        REQUIRE( list[0].t == 5 );
        REQUIRE( list[1].t == 5 );
    }

    SECTION("a ray strikes the cylinder scenario 2")
    {
        Ray ray ( Vec4::getPoint(0,0,-5) , Vec4::getVector(0,0,1) );
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
        REQUIRE( list[0].t == 4 );
        REQUIRE( list[1].t == 6 );
    }


    SECTION("a ray strikes the cylinder scenario 3")
    {
        Ray ray ( Vec4::getPoint(0.5f,0,-5) , Vec4::getVector(0.1f,1,1).normalize() );
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
//        REQUIRE(list[0].t  ==  6.80801f );
//        REQUIRE(list[1].t  ==  7.08872f );

    }
}

TEST_CASE("testing cylinder normals")
{
    Cylinder c ( new PlainMaterial() ) ;
    SECTION("scenario 1")
    {
        auto x = c.local_normal_at( Vec4::getPoint(1,0,0)) ;
        REQUIRE( x == Vec4::getVector(1,0,0)) ;
    }

    SECTION("scenario 2")
    {
        auto x = c.local_normal_at( Vec4::getPoint(0,5,-1)) ;
        REQUIRE( x == Vec4::getVector(0,0,-1)) ;
    }

    SECTION("scenario 3")
    {
        auto x = c.local_normal_at( Vec4::getPoint(0,-2,1)) ;
        REQUIRE( x == Vec4::getVector(0,0,1)) ;
    }

    SECTION("scenario 4")
    {
        auto x = c.local_normal_at( Vec4::getPoint(-1,1,0)) ;
        REQUIRE( x == Vec4::getVector(-1,0,0)) ;
    }
}

TEST_CASE("testing capped cylinders")
{
    Cylinder c( new PlainMaterial() , 1 , 2 );
    std::vector<Intersection> list;

    SECTION("intersection scenario 1")
    {
        Ray ray ( Vec4::getPoint(0,1.5f,0) , Vec4::getVector(0.1f,1,0));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("intersection scenario 2")
    {
        Ray ray ( Vec4::getPoint(0,3,-5) , Vec4::getVector(0,0,1));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("intersection scenario 3")
    {
        Ray ray ( Vec4::getPoint(0,0,-5) , Vec4::getVector(0,0,1));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("intersection scenario 4")
    {
        Ray ray ( Vec4::getPoint(0,2,-5) , Vec4::getVector(0,0,1));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("intersection scenario 5")
    {
        Ray ray ( Vec4::getPoint(0,1, -5) , Vec4::getVector(0,0,1));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("intersection scenario 6")
    {
        Ray ray ( Vec4::getPoint(0,1.5f,-2) , Vec4::getVector(0,0,1));
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
    }
}

TEST_CASE("intersecting the caps of a cylinder")
{
    Cylinder c (  new PlainMaterial() , 1 , 2 , true );
    std::vector<Intersection> list;


    SECTION("scenario 1")
    {
        Ray ray ( Vec4::getPoint(0,3,0) , Vec4::getVector(0,-1,0).normalize() );
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
    }

    SECTION("scenario 2")
    {
        Ray ray ( Vec4::getPoint(0,3,-2) , Vec4::getVector(0,-1,2).normalize() );
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
    }

//    SECTION("scenario 3")
//    {
//        Ray ray ( Vec4::getPoint(0,4,-2) , Vec4::getVector(0,-1,1).normalize() );
//        c.local_intersect( ray , list );
//
//        REQUIRE( list.size() == 2 );
//    }

    SECTION("scenario 4")
    {
        Ray ray ( Vec4::getPoint(0,0,-2) , Vec4::getVector(0,1,2).normalize() );
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
    }

//    SECTION("scenario 5")
//    {
//        Ray ray ( Vec4::getPoint(0,-1,2) , Vec4::getVector(0,1,1).normalize() );
//        c.local_intersect( ray , list );
//
//        REQUIRE( list.size() == 2 );
//    }
}


TEST_CASE()
{
    Cylinder c (  new PlainMaterial() ,  1 , 2 , true );
    std::vector<Intersection> list;

    SECTION("normal scenario 1")
    {
        auto norm = c.local_normal_at( Vec4::getPoint(0,1,0) );
        REQUIRE( norm == Vec4::getVector(0,-1,0));
    }

    SECTION("normal scenario 2")
    {
        auto norm = c.local_normal_at( Vec4::getPoint(0.5f,1,0) );
        REQUIRE( norm == Vec4::getVector(0,-1,0));
    }

    SECTION("normal scenario 3")
    {
        auto norm = c.local_normal_at( Vec4::getPoint(0,1,0.5f) );
        REQUIRE( norm == Vec4::getVector(0,-1,0));
    }

    SECTION("normal scenario 4")
    {
        auto norm = c.local_normal_at( Vec4::getPoint(0,2,0) );
        REQUIRE( norm == Vec4::getVector(0,1,0));
    }

    SECTION("normal scenario 5")
    {
        auto norm = c.local_normal_at( Vec4::getPoint(0.5f,2,0) );
        REQUIRE( norm == Vec4::getVector(0,1,0));
    }


    SECTION("normal scenario 6")
    {
        auto norm = c.local_normal_at( Vec4::getPoint(0,2,0.5f ) );
        REQUIRE( norm == Vec4::getVector(0,1,0));
    }

}