#include "catch2/catch.hpp"
#include "Mat4.h"
#include "Camera.h"
#include "Sphere.h"
#include "Material.h"
#include "World.h"
#include "Lighting.h"
#include "PlainMaterial.h"

#include "Vec3f.h"
#include "Point3f.h"

TEST_CASE("testing the inverse_view transformation matrix")
{
    SECTION("the transformation matrix for the default orientation")
    {
        Point3f from(0,0,0);
        Point3f to (0,0,-1);
        Vec3f up ( 0,1,0 );

        auto view = Mat4::view( from , to , up );
        REQUIRE( view == Mat4::IDENTITY() );
    }

    SECTION("A inverse_view transformation matrix looking in the positive z direction")
    {
        Point3f from(0,0,0);
        Point3f to (0,0,1);
        Vec3f up ( 0,1,0 );

        auto view = Mat4::view( from , to , up );
        REQUIRE( view == Mat4::IDENTITY().scale(-1,1,-1));
    }

    SECTION("the inverse_view transformation moves the world")
    {
        Point3f from(0,0,8);
        Point3f to (0,0,0);
        Vec3f up ( 0,1,0 );

        auto view = Mat4::view( from , to , up );
        REQUIRE( view == Mat4::IDENTITY().translate(0,0,-8));
    }
}

TEST_CASE("testing how the camera constructs the rays")
{
    Camera c( 201 ,101 , M_PI / 2 );
    SECTION("constructing a ray through the center of the canvas")
    {
        auto ray = c.getRayForPixel(100,50);
        REQUIRE(ray.origin == Point3f(0,0,0));
        REQUIRE(ray.direction == Vec3f(0,0,-1)) ;
    }

//    SECTION("Constructing a ray through a corner of the canvas")
//    {
//        auto ray = c.getRayForPixel(0,0);
//        REQUIRE(ray.origin == Point3f(0,0,0));
//        REQUIRE(ray.direction == Vec3f(0.66519f , 0.33259f, -0.66851f ));
//    }

    SECTION("rendering the world through the camera")
    {
        World w;
        Light light( Color3f(1,1,1) , Point3f(-10,10,-10) );
        Sphere default_unit(  new PlainMaterial (Color3f(0.8,1,0.6) , 0.1 , 0.7 , 0.2 ), Mat4::IDENTITY() );
        Sphere default_half ( new PlainMaterial() , Mat4::IDENTITY().scale(0.5f,0.5f,0.5f));

        w.add(light);
        w.add(default_unit);
        w.add(default_half);

        Camera c(  11 , 11 , M_PI/2 , Mat4::view(Point3f(0,0,-5) ,
                                                 Point3f(0,0,0) , Vec3f(0,1,0)) );

        auto ray = c.getRayForPixel(5,5);
        auto color = Lighting::color_at(w, ray, false, 0);
        REQUIRE(color == Color3f(0.380661 , 0.475827 , 0.285496 ) );
    }
}

