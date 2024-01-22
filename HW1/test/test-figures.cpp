#include "catch2/catch_all.hpp"
#include "catch2/catch_approx.hpp"
#include "Figure.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

TEST_CASE("Test triangle")
{
    double a = 8, b = 10, c = 12;
    double parameter = a + b + c; 

    Triangle t(a,b,c);

    REQUIRE(abs(parameter - t.perimeter()) <= 0.00001 );
}

TEST_CASE("Test equilateral triangle")
{
    double side = 5.0;
    double parameter = 3 * side;

    Triangle t(side, side, side);

    REQUIRE(abs(parameter - t.perimeter()) <= 0.00001);
}

TEST_CASE("Test isosceles triangle")
{
    double a = 6, b = 6, c = 7;
    double parameter = a + b + c;

    Triangle t(a, b, c);

    REQUIRE(abs(parameter - t.perimeter()) <= 0.00001);
}

TEST_CASE("Test scalene triangle")
{
    double a = 7, b = 9, c = 13;
    double parameter = a + b + c;

    Triangle t(a, b, c);

    REQUIRE(abs(parameter - t.perimeter()) <= 0.00001);
}

TEST_CASE("Test invalid triangle")
{
    double a = 4, b = 5, c = 10;  // Invalid, as the sum of any two sides should be greater than the third side
    double parameter = a + b + c;

    REQUIRE_THROWS_AS(Triangle(a, b, c), std::invalid_argument);
}

TEST_CASE("Test rectangle 1")
{
    double side1 = 818.2983888;
    double side2 = 12.273;
    double parameter = 2 * side1 + 2 * side2;

    Rectangle s(side1, side2);

    REQUIRE(abs(parameter - s.perimeter()) <= 0.00001);
}

TEST_CASE("Test rectangle - invalid side")
{
    REQUIRE_THROWS_AS(Rectangle(-2.0, 1), std::invalid_argument);
}

TEST_CASE("Test circle")
{
    double radius = 3.0;
    double parameter = 2 * M_PI * radius;

    Circle c(radius);

    REQUIRE(abs(parameter - c.perimeter()) <= 0.00001);
}

TEST_CASE("Test circle - invalid radius")
{
    double radius = -1.0; // Invalid radius

    REQUIRE_THROWS_AS(Circle(radius), std::invalid_argument);
}

TEST_CASE("Test rectangle")
{
    double length = 5.0, width = 3.0;
    double parameter = 2 * (length + width);

    Rectangle r(length, width);

    REQUIRE(abs(parameter - r.perimeter()) <= 0.00001);
}

TEST_CASE("Test rectangle - invalid sides")
{
    double length = 5.0, width = -3.0; // Invalid width

    REQUIRE_THROWS_AS(Rectangle(length, width), std::invalid_argument);
}

