#include "catch2/catch.hpp"
#include "World.h"
#include "Material.h"
#include "Ray.h"
#include "Lighting.h"
#include "PlainMaterial.h"

TEST_CASE("testing world creation")
{
    Light light( Color3f(1,1,1) , Point3f(-10,10,-10) );
    Sphere default_unit(  new PlainMaterial (Color3f(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ), Mat4::IDENTITY() );
    Sphere default_half ( new PlainMaterial() , Mat4::IDENTITY().scale(0.5f,0.5f,0.5f));

    SECTION("testing default world creation and intersection")
    {
        World w;
        w.add( light );
        w.add( default_unit );
        w.add ( default_half );

        Ray ray( Point3f(0,0,-5) , Vec3f(0,0,1) );
        auto list = w.intersect(ray, <#initializer#>);

        REQUIRE(list.size() == 4);
        REQUIRE(list[0].t == 4);
        REQUIRE(list[1].t == 4.5);
        REQUIRE(list[2].t == 5.5);
        REQUIRE(list[3].t == 6);
    }
}

TEST_CASE ("intersecting the world")
{
    Light light( Color3f(1,1,1) , Point3f(-10,10,-10) );

    Sphere default_unit(  new PlainMaterial (Color3f(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ), Mat4::IDENTITY() );
    Sphere default_half ( new PlainMaterial() , Mat4::IDENTITY().scale(0.5f,0.5f,0.5f));


    SECTION("the color when a ray misses")
    {
        World w;
        w.add( light );
        w.add ( default_unit );
        w.add( default_half );

        Ray ray( Point3f(0,0,-5) , Vec3f(0,1,0) );
        REQUIRE(Color3f(0,0,0) == Lighting::color_at(w, ray, false, 0));
    }

    SECTION("the color when a ray hits")
    {
        World w;
        w.add( light );
        w.add ( default_unit );
        w.add( default_half );

        Ray ray( Point3f(0,0,-5) , Vec3f(0,0,1) );
        auto c = Lighting::color_at(w, ray, false, 0);
        REQUIRE( c == Color3f(0.380661,0.475827,0.285496) );
    }
}

TEST_CASE("intersecting the world with some shadow calculation")
{
    SECTION("intersection in a shadow")
    {
        World world;
        Light light( Color3f(1,1,1) , Point3f(0,0,-10) );
        Sphere sphere1 ( new PlainMaterial() );
        Sphere sphere2 ( new PlainMaterial() , Mat4::IDENTITY().translate(0,0,10) );

        world.add(light);
        world.add(sphere1);
        world.add(sphere2);

        Ray ray( Point3f(0,0,5) , Vec3f(0,0,1) );
        Intersection inter( 4 , &sphere2 );

        auto color = Lighting::color_at(world, ray, true, 0);
        REQUIRE( color == Color3f(0.1,0.1,0.1)) ;
    }
}