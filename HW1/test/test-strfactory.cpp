#include "catch2/catch_all.hpp"
#include "catch2/catch_approx.hpp"
#include "StringFigureFactory.h"

TEST_CASE("Test StringFigureFactory with valid string representation of Triangle") {
    std::string input = "triangle 3 4 5";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() != nullptr);
}

TEST_CASE("Test StringFigureFactory with valid string representation of Circle") {
    std::string input = "circle 2.5";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() != nullptr);
}

TEST_CASE("Test StringFigureFactory with valid string representation of Rectangle") {
    std::string input = "rectangle 4 6";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() != nullptr);
}

TEST_CASE("Test StringFigureFactory with invalid string representation") {
    // Invalid input: missing figure type
    std::string input = "2.5";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("Test StringFigureFactory with invalid figure type") {
    // Invalid figure type
    std::string input = "rhombus 3 4 5";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("Test StringFigureFactory with invalid figure data") {
    // Invalid data for Triangle
    std::string input = "triangle 3 4";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("Test StringFigureFactory with valid long string representation of Equilateral Triangle") {
    std::string input = "triangle 5 5 5 5 5 5";
    StringFigureFactory factory(input);

    auto figure = factory.create();
    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Triangle*>(figure.get()) != nullptr);
    REQUIRE(abs(dynamic_cast<Triangle*>(figure.get())->perimeter() - 15.0) <= 0.00001);
}

TEST_CASE("Test StringFigureFactory with valid long string representation of Large Rectangle") {
    std::string input = "rectangle 100 50 100 50 100 50";
    StringFigureFactory factory(input);

    auto figure = factory.create();
    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Rectangle*>(figure.get()) != nullptr);
    REQUIRE(abs(dynamic_cast<Rectangle*>(figure.get())->perimeter() - 300.0) <= 0.00001);
}

TEST_CASE("Test StringFigureFactory with valid long string representation of Large Circle") {
    std::string input = "circle 50 50 50 50 50";
    StringFigureFactory factory(input);

    auto figure = factory.create();
    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
    REQUIRE(abs(dynamic_cast<Circle*>(figure.get())->perimeter() - 314.159) <= 0.001);
}

TEST_CASE("Test StringFigureFactory with invalid long string representation of Invalid Figure") {
    std::string input = "pentagon 4 4 4 4 4 4 4";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("Test StringFigureFactory with invalid long string representation of Negative Radius Circle") {
    std::string input = "circle -2.5 -2.5 -2.5 -2.5 -2.5";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("StringFigureFactory_Valid_SmallTriangle") {
    std::string input = "triangle 3 4 5";
    StringFigureFactory factory(input);

    auto figure = factory.create();
    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Triangle*>(figure.get()) != nullptr);
    REQUIRE(abs(dynamic_cast<Triangle*>(figure.get())->perimeter() - 12.0) <= 0.00001);
}

TEST_CASE("StringFigureFactory_Valid_TinyRectangle") {
    std::string input = "rectangle 0.1 0.2";
    StringFigureFactory factory(input);

    auto figure = factory.create();
    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Rectangle*>(figure.get()) != nullptr);
    REQUIRE(abs(dynamic_cast<Rectangle*>(figure.get())->perimeter() - 0.6) <= 0.00001);
}

TEST_CASE("StringFigureFactory_Valid_SmallCircle") {
    std::string input = "circle 1.5";
    StringFigureFactory factory(input);

    auto figure = factory.create();
    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
    REQUIRE(abs(dynamic_cast<Circle*>(figure.get())->perimeter() - 9.42478) <= 0.00001);
}

TEST_CASE("StringFigureFactory_Valid_Square") {
    std::string input = "rectangle 4 4 4 4";
    StringFigureFactory factory(input);

    auto figure = factory.create();
    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Rectangle*>(figure.get()) != nullptr);
    REQUIRE(abs(dynamic_cast<Rectangle*>(figure.get())->perimeter() - 16.0) <= 0.00001);
}

TEST_CASE("StringFigureFactory_Invalid_NegativeSideTriangle") {
    std::string input = "triangle -2 3 4";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("StringFigureFactory_Invalid_ZeroRadiusCircle") {
    std::string input = "circle 0";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("StringFigureFactory_Invalid_MissingRadiusCircle") {
    std::string input = "circle";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("StringFigureFactory_Invalid_NegativeWidthRectangle") {
    std::string input = "rectangle -2 5";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("StringFigureFactory_Invalid_MissingWidthRectangle") {
    std::string input = "rectangle 3";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}

TEST_CASE("StringFigureFactory_Invalid_EmptyString") {
    std::string input = "";
    StringFigureFactory factory(input);

    REQUIRE(factory.create() == nullptr);
}
