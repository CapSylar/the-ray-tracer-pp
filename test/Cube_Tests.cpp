#include "catch2/catch.hpp"
#include "Cube.h"
#include "Ray.h"
#include <vector>
#include <Intersection.h>
#include "PlainMaterial.h"

#include "Vec3f.h"
#include "Point3f.h"

TEST_CASE("A ray intersects a cube")
{
    Cube c( new PlainMaterial() );
    std::vector<Intersection> list;

    SECTION("+x intersection")
    {
        Ray ray ( Point3f(5,0.5f,0) , Vec3f(-1 , 0 ,0 ) ) ;
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
        REQUIRE( list[0].t == 4 );
        REQUIRE( list[1].t == 6 );
    }

    SECTION("-x intersection")
    {
        Ray ray ( Point3f(-5,0.5f,0) , Vec3f(1 , 0 ,0 ) ) ;
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
        REQUIRE( list[0].t == 4 );
        REQUIRE( list[1].t == 6 );
    }

    SECTION("+y intersection")
    {
        Ray ray ( Point3f(0.5f,5,0) , Vec3f(0 , -1 ,0 ) ) ;
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
        REQUIRE( list[0].t == 4 );
        REQUIRE( list[1].t == 6 );
    }


    SECTION("-y intersection")
    {
        Ray ray ( Point3f(0.5f,-5,0) , Vec3f(0 , 1 ,0 ) ) ;
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
        REQUIRE( list[0].t == 4 );
        REQUIRE( list[1].t == 6 );
    }

    SECTION("+z intersection")
    {
        Ray ray ( Point3f(0.5f , 0 , 5) , Vec3f(0,0,-1 ) ) ;
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
        REQUIRE( list[0].t == 4 );
        REQUIRE( list[1].t == 6 );
    }


    SECTION("-z intersection")
    {
        Ray ray ( Point3f(0.5f , 0 , -5 ) , Vec3f(0,0,1 ) ) ;
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
        REQUIRE( list[0].t == 4 );
        REQUIRE( list[1].t == 6 );
    }

    SECTION("ray starting from the inside")
    {
        Ray ray ( Point3f(0 , 0.5f , 0) , Vec3f(0,0,1 ) ) ;
        c.local_intersect( ray , list );

        REQUIRE( list.size() == 2 );
        REQUIRE( list[0].t == -1 );
        REQUIRE( list[1].t == 1 );
    }
}


TEST_CASE("ray misses the cube")
{
    Cube c ( new PlainMaterial() );
    std::vector<Intersection> list;

    SECTION("Scenario 1")
    {
        Ray ray( Point3f(-2,0,0) , Vec3f(0.2673f , 0.5345f , 0.8018f ));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("Scenario 2")
    {
        Ray ray( Point3f(0,-2,0) , Vec3f(0.8018f , 0.2673f , 0.5345f ));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }


    SECTION("Scenario 3")
    {
        Ray ray( Point3f(0,0,-2) , Vec3f(0.5345f , 0.8018f , 0.2673f ));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("Scenario 4")
    {
        Ray ray( Point3f(2,0,2) , Vec3f(0,0,-1 ));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }

    SECTION("Scenario 5")
    {
        Ray ray( Point3f(0,2,2) , Vec3f(0,-1,0 ));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }


    SECTION("Scenario 6")
    {
        Ray ray( Point3f(2,2,0) , Vec3f(-1,0,0 ));
        c.local_intersect( ray , list );

        REQUIRE( list.empty() );
    }
}

TEST_CASE("the normal of a cube")
{
    Cube c ( new PlainMaterial() );

    SECTION("scenario 1")
    {
        Point3f p = Point3f(1,0.5f,-0.8f);
        auto normal = c.local_normal_at( p );
        REQUIRE( normal == Vec3f(1,0,0) );
    }

    SECTION("scenario 2")
    {
        Point3f p = Point3f(-1,-0.2f,0.9f);
        auto normal = c.local_normal_at( p );
        REQUIRE( normal == Vec3f(-1,0,0) );
    }

    SECTION("scenario 3")
    {
        Point3f p = Point3f(-0.4f,1,-0.1f);
        auto normal = c.local_normal_at( p );
        REQUIRE( normal == Vec3f(0,1,0) );
    }

    SECTION("scenario 4")
    {
        Point3f p = Point3f(0.3f,-1,-0.7f);
        auto normal = c.local_normal_at( p );
        REQUIRE( normal == Vec3f(0,-1,0) );
    }

    SECTION("scenario 5")
    {
        Point3f p = Point3f(-0.6f,0.3f,1);
        auto normal = c.local_normal_at( p );
        REQUIRE( normal == Vec3f(0,0,1) );
    }

    SECTION("scenario 6")
    {
        Point3f p = Point3f(0.4f,0.4f,-1);
        auto normal = c.local_normal_at( p );
        REQUIRE( normal == Vec3f(0,0,-1) );
    }

    SECTION("scenario 7")
    {
        Point3f p = Point3f(1,1,1);
        auto normal = c.local_normal_at( p );
        REQUIRE( normal == Vec3f(1,0,0) );
    }

    SECTION("scenario 8")
    {
        Point3f p = Point3f(-1,-1,-1);
        auto normal = c.local_normal_at( p );
        REQUIRE( normal == Vec3f(-1,0,0) );
    }
}