#include "catch2/catch_all.hpp"
#include "catch2/catch_approx.hpp"
#include "StreamFigureFactory.h"

TEST_CASE("Test StreamFigureFactory - Create Triangle") {
    std::istringstream input("triangle 3 4 5");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Triangle*>(figure.get()) != nullptr);
}

TEST_CASE("Test StreamFigureFactory - Create Circle") {
    std::istringstream input("circle 2.5");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Circle*>(figure.get()) != nullptr);
}

TEST_CASE("Test StreamFigureFactory - Create Rectangle") {
    std::istringstream input("rectangle 4 6");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure != nullptr);
    REQUIRE(dynamic_cast<Rectangle*>(figure.get()) != nullptr);
}

TEST_CASE("Test StreamFigureFactory - Invalid Input") {
    std::istringstream input("invalid_type 1 2 3");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure == nullptr);
}


TEST_CASE("Test StreamFigureFactory - Create Triangle with Invalid Input") {
    // Invalid side lengths for a triangle
    std::istringstream input("triangle 1 1 10");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure == nullptr);
}

TEST_CASE("Test StreamFigureFactory - Create Circle with Invalid Input") {
    // Negative radius for a circle
    std::istringstream input("circle -2.5");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure == nullptr);
}

TEST_CASE("Test StreamFigureFactory - Create Rectangle with Invalid Input") {
    // Negative sides for a rectangle
    std::istringstream input("rectangle -4 6");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure == nullptr);
}

TEST_CASE("Test StreamFigureFactory - Create Figure with Empty Input") {
    // Empty input string
    std::istringstream input("");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure == nullptr);
}

TEST_CASE("Test StreamFigureFactory - Create Figure with Malformed Input") {
    // Malformed input string
    std::istringstream input("malformed_input");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure == nullptr);
}

TEST_CASE("Test StreamFigureFactory - Create Figure with Unknown Type") {
    // Unknown figure type
    std::istringstream input("unknown_type 1 2 3");
    StreamFigureFactory factory(input);

    auto figure = factory.create();

    REQUIRE(figure == nullptr);
}

TEST_CASE("Test StreamFigureFactory - Create Multiple Figures") {
    std::istringstream input("triangle 3 4 5\ncircle 2.5\nrectangle 4 6");
    StreamFigureFactory factory(input);

    auto figure1 = factory.create();
    auto figure2 = factory.create();
    auto figure3 = factory.create();

    REQUIRE(figure1 != nullptr);
    REQUIRE(dynamic_cast<Triangle*>(figure1.get()) != nullptr);

    REQUIRE(figure2 != nullptr);
    REQUIRE(dynamic_cast<Circle*>(figure2.get()) != nullptr);

    REQUIRE(figure3 != nullptr);
    REQUIRE(dynamic_cast<Rectangle*>(figure3.get()) != nullptr);
}
