#include "catch2/catch.hpp"
#include "Material.h"
#include "Lighting.h"
#include "World.h"
#include "LightComputations.h"
#include "Intersection.h"
#include "Plane.h"
#include "PlainMaterial.h"

#include "Vec3f.h"
#include "Point3f.h"

TEST_CASE( "testing lights n materials" )
{
    SECTION("testing the creation of lights")
    {
        Light light( Color3f(1,1,1) , Point3f(0,0,0));
        REQUIRE(light.position == Point3f());
        REQUIRE(light.intensity == Color3f());
    }

    SECTION("testing the default material")
    {
        Material *mat = new PlainMaterial() ;
        REQUIRE(mat->get_albedo(Point3f(0,0,0)) == Color3f());
        REQUIRE(mat->shininess == 200 );
        REQUIRE(mat->specular == 0.9f);
        REQUIRE(mat->diffuse == 0.9f);
        REQUIRE(mat->ambient == 0.1f);
        REQUIRE(mat->reflectance == 0.0f);
        REQUIRE(mat->transparency == 0.0f );
        REQUIRE( mat->refractive_index == 1.0f );
    }

    SECTION("testing the glass material")
    {
        Material *mat = PlainMaterial::getGlassMaterial();
        REQUIRE(mat->transparency == 1);
        REQUIRE(mat->refractive_index == 1.5f);
        delete(mat);
    }
}

TEST_CASE("testing phong shading")
{
    Sphere def ( new PlainMaterial() );
    Light light( Color3f(1,1,1) , Point3f(0,0,-10));
    Vec3f normalv = Vec3f(0,0,-1);
    Point3f position = Point3f() ;

    SECTION("default setting")
    {
        LightComputations comps ( def , position , Vec3f(0, 0, -1) , Vec3f(0, 0, -1) ) ;
        auto res = Lighting::get_surface_color( light , comps , false );

        REQUIRE( res == Color3f(1.9,1.9,1.9)) ;
    }

    SECTION("get_surface_color with the eye between light and surface, eye offset 45")
    {
        Vec3f eyev = Vec3f(0, sqrtf(2)/2 , sqrtf(2)/2 );

        LightComputations comps ( def , position , normalv , eyev );
        auto result = Lighting::get_surface_color( light, comps , false);

        REQUIRE( result == Color3f(1,1,1) );
    }

    SECTION("get_surface_color with eye opposite surface, light offset 45")
    {
        Vec3f eyev = Vec3f(0,0,-1);
        Light this_light( Color3f() , Point3f(0,10,-10) );

        LightComputations comps ( def , position , normalv , eyev );
        auto result = Lighting::get_surface_color( this_light , comps , false);
        REQUIRE( result == Color3f(0.736396,0.736396,0.736396) );
    }

//    SECTION("get_surface_color with eye in the path of the reflection vector")
//    {
//        Vector eyev = Vec3f(0,-sqrtf(2)/2,-sqrtf(2)/2 );
//        Light this_light( Color3f() , Point3f(0,10,-10) );
//
//        LightComputations comps ( def , position , normalv , eyev );
//        auto result = Lighting::get_surface_color( this_light , comps , false);
//
//        REQUIRE( result == Color3f(1.63639,1.63639,1.63639));
//    }

    SECTION("get_surface_color with the light behind the surface")
    {
        Vec3f eyev = Vec3f( 0 , 0, -1 );
        Light this_light( Color3f() , Point3f(0,0,10) );

        LightComputations comps ( def , position , normalv , eyev );
        auto result = Lighting::get_surface_color( this_light , comps , false);

        REQUIRE( result == Color3f(0.1,0.1,0.1) );
    }
}

TEST_CASE("testing for shadows")
{
    World w;
    Light light( Color3f(1,1,1) , Point3f(-10,10,-10) );

    Sphere default_unit(  new PlainMaterial (Color3f(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ), Mat4::IDENTITY() );
    Sphere default_half ( new PlainMaterial() , Mat4::IDENTITY().scale(0.5f,0.5f,0.5f));

    w.add(light);
    w.add(default_unit);
    w.add(default_half);

    SECTION("there is no shadow when nothing is collinear with point and light")
    {
        Point3f p (0,10,0);
        REQUIRE( Lighting::is_shadowed( w , p ) == false );
    }

    SECTION("the shadow when an object is between point and the light")
    {
        Point3f p (10,-10,10);
        REQUIRE( Lighting::is_shadowed( w , p ) == true );
    }

    SECTION("there is no shadow when an object is behind the light")
    {
        Point3f p (-20 , 20 ,-20 );
        REQUIRE( Lighting::is_shadowed( w , p ) == false );
    }

    SECTION("there is now shadow when a object is behind the point")
    {
        Point3f p (-2 , 2 , -2);
        REQUIRE( Lighting::is_shadowed( w , p ) == false );
    }
}


TEST_CASE("testing lighting with reflections ON")
{
    World w;
    Light light( Color3f(1,1,1) , Point3f(-10,10,-10) );
    Sphere default_unit(  new PlainMaterial (Color3f(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ), Mat4::IDENTITY() );
    Sphere default_half ( new PlainMaterial() , Mat4::IDENTITY().scale(0.5f,0.5f,0.5f));

    w.add(light);
    w.add(default_half);
    w.add(default_unit);

    SECTION("the reflected color for a non-reflective material")
    {
        Ray ray( Point3f(0,0,0) , Vec3f(0,0,1) );
        default_half.material->ambient = 1;

        Intersection inter( 1 , &default_half );
        LightComputations comps ( inter , ray );
        REQUIRE(Lighting::get_reflected_color(w, comps, 0) == Color3f(0, 0, 0) );
    }

    SECTION("the reflected color only for a reflective material")
    {
        Plane p(  new PlainMaterial() , Mat4().translate(0,-1,0) );
        p.material->reflectance = 0.5f;

        w.add(p);
        Ray ray( Point3f(0,0,-3) , Vec3f(0, -sqrtf(2)/2, sqrtf(2)/2 ) );
        Intersection inter(sqrtf(2) , &p );
        LightComputations comps ( inter , ray );

        REQUIRE(Lighting::get_reflected_color(w, comps, 1) == Color3f(0.190333 , 0.237916 , 0.142749 ) );
    }

    SECTION("the reflected color for a reflective material")
    {
        Plane p( new PlainMaterial() , Mat4().translate(0,-1,0) );
        p.material->reflectance = 0.5f;

        w.add(p);
        Ray ray( Point3f(0,0,-3) , Vec3f(0, -sqrtf(2)/2, sqrtf(2)/2 ) );
        Intersection inter(sqrtf(2) , &p );
        LightComputations comps ( inter , ray );

        REQUIRE(Lighting::color_at(w, ray, true, 1) == Color3f(0.876758 , 0.924341 , 0.829174 ) );
    }
}
