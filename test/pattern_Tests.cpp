#include "catch2/catch.hpp"

#include "StripedPattern.h"
#include "Color.h"
#include "Sphere.h"
#include "PatternMaterial.h"
#include "GradientPattern.h"
#include "CheckerPattern.h"
#include "RingPattern.h"

TEST_CASE("striped pattern tests")
{
    StripedPattern x;

    SECTION("testing striped pattern creation")
    {
        REQUIRE( x.a == Color(1,1,1));
        REQUIRE( x.b == Color(0,0,0));
    }

    SECTION("the pattern should be constant in y")
    {
        REQUIRE(x.local_color_at(Vec4::getPoint(0, 0, 0)) == Color(1, 1, 1));
        REQUIRE(x.local_color_at(Vec4::getPoint(0, 1, 0)) == Color(1, 1, 1));
        REQUIRE(x.local_color_at(Vec4::getPoint(0, 2, 0)) == Color(1, 1, 1));
    }

    SECTION("the pattern should be constant in z")
    {
        REQUIRE(x.local_color_at(Vec4::getPoint(0, 0, 0)) == Color(1, 1, 1));
        REQUIRE(x.local_color_at(Vec4::getPoint(0, 0, 1)) == Color(1, 1, 1));
        REQUIRE(x.local_color_at(Vec4::getPoint(0, 0, 2)) == Color(1, 1, 1));
    }

    SECTION("the pattern should alternate in x")
    {
        REQUIRE(x.local_color_at(Vec4::getPoint(0, 0, 0)) == Color(1, 1, 1));
        REQUIRE(x.local_color_at(Vec4::getPoint(0.9f, 0, 0)) == Color(1, 1, 1));
        REQUIRE(x.local_color_at(Vec4::getPoint(1, 0, 0)) == Color(0, 0, 0));
        REQUIRE(x.local_color_at(Vec4::getPoint(-0.1f, 0, 0)) == Color(0, 0, 0));
        REQUIRE(x.local_color_at(Vec4::getPoint(-1, 0, 0)) == Color(0, 0, 0));
        REQUIRE(x.local_color_at(Vec4::getPoint(-1.1f, 0, 0)) == Color(1, 1, 1));
    }
}

TEST_CASE("tests for transforming stripped patterns")
{
    SECTION("Stripes with an object transformation")
    {
        Sphere s(nullptr , Mat4::IDENTITY().scale(2,2,2));
        s.material = new PatternMaterial( new StripedPattern( s ) );

        REQUIRE( s.material->get_albedo(Vec4::getPoint(1.5f,0,0)) == Color(1,1,1));
    }

    SECTION("Stripes with an pattern transformation")
    {
        Sphere s(nullptr);
        s.material = new PatternMaterial( new StripedPattern( s , Mat4::IDENTITY().scale(2,2,2)) );

        REQUIRE( s.material->get_albedo(Vec4::getPoint(1.5f,0,0)) == Color(1,1,1));
    }

    SECTION("Stripes with an object and pattern transformation")
    {
        Sphere s(nullptr , Mat4::IDENTITY().scale(2,2,2));
        s.material = new PatternMaterial( new StripedPattern( s , Mat4::IDENTITY().translate(0.5f,0,0) ) );

        REQUIRE( s.material->get_albedo(Vec4::getPoint(2.5f,0,0)) == Color(1,1,1));
    }
}

TEST_CASE("tests for gradient patterns")
{
    SECTION("a gradient linearly interpolated between Colors")
    {
        GradientPattern pattern;

        REQUIRE(pattern.local_color_at(Vec4::getPoint(0,0,0)) == Color(1,1,1) );
        REQUIRE(pattern.local_color_at(Vec4::getPoint(0.25f,0,0)) == Color(0.75f,0.75f,0.75f) );
        REQUIRE(pattern.local_color_at(Vec4::getPoint(0.5f,0,0)) == Color(0.5f,0.5f,0.5f) );
        REQUIRE(pattern.local_color_at(Vec4::getPoint(0.75f,0,0)) == Color(0.25f,0.25f,0.25f) );

    }
}


TEST_CASE("tests for ring patterns")
{
    RingPattern pattern;
    SECTION("a ring should extend in both x and z")
    {
        REQUIRE( pattern.local_color_at( Vec4::getPoint(0,0,0))  == Color(1,1,1));
        REQUIRE( pattern.local_color_at( Vec4::getPoint(1,0,0))  == Color(0,0,0));
        REQUIRE( pattern.local_color_at( Vec4::getPoint(0,0,1))  == Color(0,0,0));
        REQUIRE( pattern.local_color_at( Vec4::getPoint(0.708f,0,0.708f))  == Color(0,0,0));
    }
}

TEST_CASE("tests for checker patterns")
{
    CheckerPattern pattern;

    SECTION("checker pattern should repeat in x ")
    {
        REQUIRE(pattern.local_color_at(Vec4::getPoint(0,0,0)) == Color(1,1,1) );
        REQUIRE(pattern.local_color_at(Vec4::getPoint(0.99f,0,0)) == Color(1,1,1) );
        REQUIRE(pattern.local_color_at(Vec4::getPoint(1.01f,0,0)) == Color(0,0,0) );
    }

    SECTION("checker pattern should repeat in y ")
    {
        REQUIRE(pattern.local_color_at(Vec4::getPoint(0,0.99f,0)) == Color(1,1,1) );
        REQUIRE(pattern.local_color_at(Vec4::getPoint(0,1.01f,0)) == Color(0,0,0) );
    }

    SECTION("checker pattern should repeat in z ")
    {
        REQUIRE(pattern.local_color_at(Vec4::getPoint(0,0,0.99f)) == Color(1,1,1) );
        REQUIRE(pattern.local_color_at(Vec4::getPoint(0,0,1.01f)) == Color(0,0,0) );
    }
}