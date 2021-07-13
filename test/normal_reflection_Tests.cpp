#include "catch2/catch.hpp"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include "Intersection.h"
#include "LightComputations.h"
#include "PlainMaterial.h"

TEST_CASE("normal tests")
{
    Sphere s ( new PlainMaterial() );
    SECTION("the normal on a sphere at a point on the x axis")
    {
        auto test = s.normal_at(Point3f(1,0,0));
        REQUIRE( test == Vec3f(1,0,0) ) ;
    }

    SECTION("the normal on a sphere at a point on the y axis")
    {
        auto test = s.normal_at(Point3f(0,1,0));
        REQUIRE( test == Vec3f(0,1,0) ) ;
    }

    SECTION("the normal on a sphere at a point on the z axis")
    {
        auto test = s.normal_at(Point3f(0,0,1));
        REQUIRE( test == Vec3f(0,0,1) ) ;
    }

    SECTION("the normal of a sphere on a nonaxial point")
    {
        float sqrt3over3 = sqrtf(3)/3;
        auto test = s.normal_at(Point3f(sqrt3over3,sqrt3over3,sqrt3over3));
        REQUIRE( test == Vec3f(sqrt3over3,sqrt3over3,sqrt3over3) ) ;
    }

    SECTION("computed normal on a translated sphere")
    {
        Sphere local ( new PlainMaterial() ,Mat4::IDENTITY().translate(0,1,0)) ;
        auto n = local.normal_at( Point3f(0,1.70711,-0.70711));
        REQUIRE( n == Vec3f(0,0.707107,-0.707107));
    }

    SECTION("computed normal on a transformed sphere")
    {
        Sphere local ( new PlainMaterial() , Mat4::IDENTITY().rotate_z(M_PI/5).scale(1,0.5,1) );
        auto n = local.normal_at( Point3f(0, sqrtf(2)/2,-sqrtf(2)/2));
        REQUIRE( n == Vec3f(0,0.970143,-0.242536));
    }
}

TEST_CASE("testing reflection of vectors")
{
    SECTION("reflecting a vector approaching at 45")
    {
        auto v = Vec3f(1,-1,0);
        auto n = Vec3f(0,1,0);
        auto r = Ray::reflect( v , n );
        REQUIRE( r == Vec3f(1,1,0));
    }

    SECTION("reflecting a vector off a slanted surface")
    {
        auto v = Vec3f(0,-1,0);
        auto n = Vec3f(sqrtf(2)/2, sqrtf(2)/2,0);
        auto r = Ray::reflect( v , n );
        REQUIRE( r == Vec3f(1,0,0));
    }
}

TEST_CASE("precomputing the reflection vector")
{
    Plane p ( new PlainMaterial() );
    float sqrt2over2 = sqrtf(2) / 2;
    Ray ray( Point3f(0,1,-1) , Vec3f(0,-sqrt2over2 , sqrt2over2 )) ;
    Intersection inter(sqrtf(2) , &p );

    LightComputations comps ( inter , ray );
    REQUIRE( comps.reflected == Vec3f( 0 , sqrt2over2 , sqrt2over2 ) );
}