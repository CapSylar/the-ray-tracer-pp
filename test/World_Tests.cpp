#include "catch2/catch.hpp"
#include "World.h"
#include "Material.h"
#include "Ray.h"
#include "tracing.h"

TEST_CASE("testing world creation")
{
    Light light( Color(1,1,1) , Vec4::getPoint(-10,10,-10) );
    Sphere default_unit(  Mat4::IDENTITY() ,  Material( Color(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ) );
    Sphere default_half;
    default_half.transform.scale(0.5,0.5,0.5);

    SECTION("testing default world creation and intersection")
    {
        World w;
        w.add( light );
        w.add( default_unit );
        w.add ( default_half );

        Ray ray( Vec4::getPoint(0,0,-5) , Vec4::getVector(0,0,1) );
        auto list = w.intersect( ray );

        REQUIRE(list.size() == 4);
        REQUIRE(list[0].t == 4);
        REQUIRE(list[1].t == 4.5);
        REQUIRE(list[2].t == 5.5);
        REQUIRE(list[3].t == 6);
    }
}

TEST_CASE ("intersecting the world")
{
    Light light( Color(1,1,1) , Vec4::getPoint(-10,10,-10) );
    Sphere default_unit(  Mat4::IDENTITY() ,  Material( Color(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ) );
    Sphere default_half;
    default_half.transform.scale(0.5,0.5,0.5);

    SECTION("the color when a ray misses")
    {
        World w;
        w.add( light );
        w.add ( default_unit );
        w.add( default_half );

        Ray ray( Vec4::getPoint(0,0,-5) , Vec4::getVector(0,1,0) );
        REQUIRE(Color(0,0,0) == Lighting::color_at( w , ray ));
    }

    SECTION("the color when a ray hits")
    {
        World w;
        w.add( light );
        w.add ( default_unit );
        w.add( default_half );

        Ray ray( Vec4::getPoint(0,0,-5) , Vec4::getVector(0,0,1) );
        auto c = Lighting::color_at( w , ray );
        REQUIRE( c == Color(0.380661,0.475827,0.285496) );
    }
}

TEST_CASE("intersecting the world with some shadow calculation")
{
    SECTION("intersection in a shadow")
    {
        World world;
        Light light( Color(1,1,1) , Vec4::getPoint(0,0,-10) );
        Sphere sphere1;
        Sphere sphere2 (  Mat4::IDENTITY().translate(0,0,10) );

        world.add(light);
        world.add(sphere1);
        world.add(sphere2);

        Ray ray( Vec4::getPoint(0,0,5) , Vec4::getVector(0,0,1) );
        Intersection inter( 4 , sphere2 );

        auto color = Lighting::color_at( world , ray , true );
        REQUIRE( color == Color(0.1,0.1,0.1)) ;
    }
}