#include "catch2/catch.hpp"
#include "Material.h"
#include "tracing.h"

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
    }
}

TEST_CASE("testing phong shading")
{
    Material m;
    Light light( Color(1,1,1) , Vec4::getPoint(0,0,-10));
    Vector normalv = Vec4::getVector(0,0,-1);
    Point position = Vec4::getPoint() ;

    SECTION("default setting")
    {
        auto res =  Lighting::lighting( m , light , position , Vec4::getVector(0,0,-1) , Vec4::getVector(0,0,-1) , false );

        REQUIRE( res == Color(1.9,1.9,1.9)) ;
    }

    SECTION("lighting with the eye between light and surface, eye offset 45")
    {
        Vector eyev = Vec4::getVector(0, sqrtf(2)/2 , sqrtf(2)/2 );
        auto result = Lighting::lighting ( m , light , position , eyev , normalv , false );

        REQUIRE( result == Color(1,1,1) );
    }

    SECTION("lighting with eye opposite surface, light offset 45")
    {
        Vector eyev = Vec4::getVector(0,0,-1);
        Light this_light( Color() , Vec4::getPoint(0,10,-10) );
        auto result = Lighting::lighting( m , this_light , position , eyev , normalv , false  );
        REQUIRE( result == Color(0.736396,0.736396,0.736396) );
    }

//    SECTION("lighting with eye in the path of the reflection vector")
//    {
//        Vector eyev = Vec4::getVector(0,-sqrtf(2)/2,-sqrtf(2)/2 );
//        Light this_light( Color() , Vec4::getPoint(0,10,-10) );
//        auto result = lighting( m , this_light , position , eyev , normalv );
//        REQUIRE( result == Color(1.63639,1.63639,1.63639));
//    }

    SECTION("lighting with the light behind the surface")
    {
        Vector eyev = Vec4::getVector( 0 , 0, -1 );
        Light this_light( Color() , Vec4::getPoint(0,0,10) );
        auto result = Lighting::lighting( m , this_light , position , eyev , normalv , false );
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