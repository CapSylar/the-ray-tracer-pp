#include "catch2/catch.hpp"
#include "Material.h"
#include "tracing.h"
#include "World.h"
#include "LightComputations.h"
#include "Intersection.h"
#include "Plane.h"

TEST_CASE( "testing lights n materials" )
{
    SECTION("testing the creation of lights")
    {
        Light light( Color(1,1,1) , Vec4::getPoint(0,0,0));
        REQUIRE(light.position == Vec4::getPoint());
        REQUIRE(light.intensity == Color());
    }

    SECTION("testing the default material")
    {
        Material mat;
        REQUIRE(mat.color == Color());
        REQUIRE(mat.shininess == 200 );
        REQUIRE(mat.specular == 0.9f);
        REQUIRE(mat.diffuse == 0.9f);
        REQUIRE(mat.ambient == 0.1f);
        REQUIRE(mat.reflectance == 0.0f);
    }
}

TEST_CASE("testing phong shading")
{
    Sphere def;
    Light light( Color(1,1,1) , Vec4::getPoint(0,0,-10));
    Vector normalv = Vec4::getVector(0,0,-1);
    Point position = Vec4::getPoint() ;

    SECTION("default setting")
    {
        LightComputations comps ( def , position , Vec4::getVector(0, 0, -1) , Vec4::getVector(0, 0, -1) ) ;
        auto res = Lighting::get_surface_color( light , comps , false );

        REQUIRE( res == Color(1.9,1.9,1.9)) ;
    }

    SECTION("get_surface_color with the eye between light and surface, eye offset 45")
    {
        Vector eyev = Vec4::getVector(0, sqrtf(2)/2 , sqrtf(2)/2 );

        LightComputations comps ( def , position , normalv , eyev );
        auto result = Lighting::get_surface_color( light, comps , false);

        REQUIRE( result == Color(1,1,1) );
    }

    SECTION("get_surface_color with eye opposite surface, light offset 45")
    {
        Vector eyev = Vec4::getVector(0,0,-1);
        Light this_light( Color() , Vec4::getPoint(0,10,-10) );

        LightComputations comps ( def , position , normalv , eyev );
        auto result = Lighting::get_surface_color( this_light , comps , false);
        REQUIRE( result == Color(0.736396,0.736396,0.736396) );
    }

//    SECTION("get_surface_color with eye in the path of the reflection vector")
//    {
//        Vector eyev = Vec4::getVector(0,-sqrtf(2)/2,-sqrtf(2)/2 );
//        Light this_light( Color() , Vec4::getPoint(0,10,-10) );
//
//        LightComputations comps ( def , position , normalv , eyev );
//        auto result = Lighting::get_surface_color( this_light , comps , false);
//
//        REQUIRE( result == Color(1.63639,1.63639,1.63639));
//    }

    SECTION("get_surface_color with the light behind the surface")
    {
        Vector eyev = Vec4::getVector( 0 , 0, -1 );
        Light this_light( Color() , Vec4::getPoint(0,0,10) );

        LightComputations comps ( def , position , normalv , eyev );
        auto result = Lighting::get_surface_color( this_light , comps , false);

        REQUIRE( result == Color(0.1,0.1,0.1) );
    }
}

TEST_CASE("testing for shadows")
{
    World w;
    Light light( Color(1,1,1) , Vec4::getPoint(-10,10,-10) );
    Sphere default_unit( Mat4::IDENTITY() , Material( Color(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ) );
    Sphere default_half;
    default_half.transform.scale(0.5,0.5,0.5);

    w.add(light);
    w.add(default_unit);
    w.add(default_half);

    SECTION("there is no shadow when nothing is collinear with point and light")
    {
        Point p (0,10,0);
        REQUIRE( Lighting::is_shadowed( w , p ) == false );
    }

    SECTION("the shadow when an object is between point and the light")
    {
        Point p (10,-10,10);
        REQUIRE( Lighting::is_shadowed( w , p ) == true );
    }

    SECTION("there is no shadow when an object is behind the light")
    {
        Point p (-20 , 20 ,-20 );
        REQUIRE( Lighting::is_shadowed( w , p ) == false );
    }

    SECTION("there is now shadow when a object is behind the point")
    {
        Point p (-2 , 2 , -2);
        REQUIRE( Lighting::is_shadowed( w , p ) == false );
    }
}


TEST_CASE("testing lighting with reflections ON")
{
    World w;
    Light light( Color(1,1,1) , Vec4::getPoint(-10,10,-10) );
    Sphere default_unit(  Mat4::IDENTITY() ,  Material( Color(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ) );
    Sphere default_half;
    default_half.transform.scale(0.5,0.5,0.5);

    w.add(light);
    w.add(default_half);
    w.add(default_unit);

    SECTION("the reflected color for a non-reflective material")
    {
        Ray ray( Vec4::getPoint(0,0,0) , Vec4::getVector(0,0,1) );
        default_half.material.ambient = 1;

        Intersection inter( 1 , default_half );
        LightComputations comps ( inter , ray );
        REQUIRE(Lighting::get_reflected_color(w, comps, 0) == Color(0, 0, 0) );
    }

    SECTION("the reflected color only for a reflective material")
    {
        Plane p( Mat4().translate(0,-1,0) );
        p.material.reflectance = 0.5f;

        w.add(p);
        Ray ray( Vec4::getPoint(0,0,-3) , Vec4::getVector(0, -sqrtf(2)/2, sqrtf(2)/2 ) );
        Intersection inter(sqrtf(2) , p );
        LightComputations comps ( inter , ray );

        REQUIRE(Lighting::get_reflected_color(w, comps, 1) == Color(0.190333 , 0.237916 , 0.142749 ) );
    }

    SECTION("the reflected color for a reflective material")
    {
        Plane p( Mat4().translate(0,-1,0) );
        p.material.reflectance = 0.5f;

        w.add(p);
        Ray ray( Vec4::getPoint(0,0,-3) , Vec4::getVector(0, -sqrtf(2)/2, sqrtf(2)/2 ) );
        Intersection inter(sqrtf(2) , p );
        LightComputations comps ( inter , ray );

        REQUIRE(Lighting::color_at(w, ray, true, 1) == Color(0.876758 , 0.924341 , 0.829174 ) );
    }
}
