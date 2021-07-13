#include <Plane.h>
#include "catch2/catch.hpp"
#include "Sphere.h"
#include "Ray.h"
#include "Intersection.h"
#include "LightComputations.h"
#include "Lighting.h"
#include "World.h"
#include "utilities.h"
#include "PlainMaterial.h"

TEST_CASE("testing intersections")
{
    Sphere a ( PlainMaterial::getGlassMaterial()  , Mat4::IDENTITY().scale(2,2,2) );
    a.material->refractive_index = 1.5f;

    Sphere b ( PlainMaterial::getGlassMaterial() , Mat4::IDENTITY().translate(0,0,-0.25) );
    b.material->refractive_index = 2.0f;

    Sphere c ( PlainMaterial::getGlassMaterial() , Mat4::IDENTITY().translate(0,0,0.25) );
    c.material->refractive_index = 2.5f;

    Ray ray ( Point3f(0,0,-4) , Vec3f(0,0,1) );

    std::vector<Intersection> list;
    list.emplace_back( 2 , &a );
    list.emplace_back( 2.75f , &b );
    list.emplace_back( 3.25f , &c );
    list.emplace_back( 4.75f , &b );
    list.emplace_back( 5.25f , &c );
    list.emplace_back( 6 , &a );

    SECTION("finding n1 and n2 at various intersections")
    {
        LightComputations comps ( list[0] , ray , list );
        REQUIRE( comps.n1 == 1 );
        REQUIRE( comps.n2 == 1.5f );
    }

    SECTION("finding n1 and n2 at various intersections")
    {
        LightComputations comps ( list[1] , ray , list );
        REQUIRE( comps.n1 == 1.5 );
        REQUIRE( comps.n2 == 2 );
    }

    SECTION("finding n1 and n2 at various intersections")
    {
        LightComputations comps ( list[2] , ray , list );
        REQUIRE( comps.n1 == 2 );
        REQUIRE( comps.n2 == 2.5f );
    }

    SECTION("finding n1 and n2 at various intersections")
    {
        LightComputations comps ( list[3] , ray , list );
        REQUIRE( comps.n1 == 2.5f );
        REQUIRE( comps.n2 == 2.5f );
    }

    SECTION("finding n1 and n2 at various intersections")
    {
        LightComputations comps ( list[4] , ray , list );
        REQUIRE( comps.n1 == 2.5f );
        REQUIRE( comps.n2 == 1.5f );
    }

    SECTION("finding n1 and n2 at various intersections")
    {
        LightComputations comps ( list[5] , ray , list );
        REQUIRE( comps.n1 == 1.5f );
        REQUIRE( comps.n2 == 1.0f );
    }
}


TEST_CASE("testing refraction")
{
    World w;
    Light light( Color3f(1,1,1) , Point3f(-10,10,-10) );
    Sphere default_unit(  new PlainMaterial (Color3f(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ), Mat4::IDENTITY() );
    Sphere default_half ( new PlainMaterial() , Mat4::IDENTITY().scale(0.5f,0.5f,0.5f));

    w.add(light);
    w.add(default_unit);
    w.add(default_half);

    default_unit.material = PlainMaterial::getGlassMaterial() ; // make it glass


    SECTION("the refracted color at the maximum recursive depth")
    {
        Ray ray ( Point3f(0,0,-5 ) , Vec3f(0,0,1)) ;
        std::vector<Intersection> list;
        list.emplace_back( 4 , &default_unit );
        list.emplace_back( 6 , &default_unit );

        LightComputations comps ( list[0] , ray , list );

        REQUIRE( Lighting::get_refracted_color( w , comps , 0 ) == Color3f(0,0,0) );
    }

    SECTION("the refracted color under total internal reflection")
    {
        Ray ray ( Point3f(0,0,sqrtf(2)/2 ) , Vec3f(0,1,0)) ;
        std::vector<Intersection> list;
        list.emplace_back( -sqrtf(2)/2 , &default_unit );
        list.emplace_back( sqrtf(2)/2 , &default_unit );

        LightComputations comps ( list[1] , ray , list );

        REQUIRE( Lighting::get_refracted_color( w, comps , 5 ) == Color3f(0,0,0));
    }
}

TEST_CASE("testing schlick's approximation")
{
    SECTION("the approx under total internal reflection")
    {
        Sphere p ( PlainMaterial::getGlassMaterial() );
        Ray ray ( Point3f(0,0, sqrtf(2)/2 ) , Vec3f(0,1,0 ) );
        std::vector<Intersection> list;
        list.emplace_back( -sqrtf(2)/2 , &p );
        list.emplace_back( sqrtf(2)/2 , &p );

        LightComputations comps(  list[1] , ray , list );
        REQUIRE(isEqualF(Lighting::get_schlick_factor(comps), 1)  );
    }

    SECTION("the approx with a perpendicular viewing angle")
    {
        Sphere p ( PlainMaterial::getGlassMaterial() );
        Ray ray ( Point3f(0,0, 0 ) , Vec3f(0,1,0 ) );
        std::vector<Intersection> list;
        list.emplace_back( -1 , &p );
        list.emplace_back( 1 , &p );

        LightComputations comps ( list[1] , ray , list );
        REQUIRE(isEqualF(Lighting::get_schlick_factor(comps), 0.04f) ) ;
    }


    SECTION("the approx with a small angle and n2 > n1")
    {
        Sphere p ( PlainMaterial::getGlassMaterial() );
        Ray ray ( Point3f(0,0.99f, -2 ) , Vec3f(0,0,1 ) );
        std::vector<Intersection> list;
        list.emplace_back( 1.8589f , &p );

        LightComputations comps ( list[0] , ray , list );
        REQUIRE(isEqualF(Lighting::get_schlick_factor(comps), 0.48873f) ) ;
    }

//    SECTION("test it with a reflective and transparent material")
//    {
//        World w;
//        Light light( Color3f(1,1,1) , Point3f(-10,10,-10) );
//        Sphere default_unit( Mat4::IDENTITY() , Material( Color3f(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ) );
//        Sphere default_half;
//        default_half.inverse_trans.scale(0.5,0.5,0.5);
//
//        w.add(light);
//        w.add(default_unit);
//        w.add(default_half);
//
//        Ray ray ( Point3f(0,0,-3) , Vec3f(0,-sqrtf(2)/2 , sqrtf(2)/2 ) );
//        Plane floor( Mat4::IDENTITY().translate(0,-1,0) );
//        floor.material.transparency = 0.5f;
//        floor.material.reflectance = 0.5f;
//        floor.material.refractive_index = 1.5f;
//
//        w.add(floor);
//        Sphere p ( Mat4::IDENTITY().translate(0,-3.5f,-0.5f));
//
//        p.material.color = Color3f(1,0,0);
//        p.material.ambient = 0.5f;
//
//        w.add( p );
//
//        std::vector<Intersection> list ( 1 , ( Intersection(sqrtf(2) , floor) ) );
//        LightComputations comps ( list[0] , ray , list );
//        REQUIRE( Lighting::shade_hit(  w , comps , true , 5 ) == Color3f(0.933915 , 0.696434 , 0.692431 ) );
//    }
}