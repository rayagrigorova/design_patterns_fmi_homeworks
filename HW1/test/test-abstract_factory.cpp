#include "catch2/catch_all.hpp"
#include "AbstractFigureFactory.h"

#include "StreamFigureFactory.h"
#include "StringFigureFactory.h"
#include "RandomFigureFactory.h"

TEST_CASE("Create RandomFigureFactory") {
    AbstractFigureFactory& factory = AbstractFigureFactory::getInstance();
    auto figureFactory = factory.create("Random");

    REQUIRE(figureFactory != nullptr);
    REQUIRE(dynamic_cast<RandomFigureFactory*>(figureFactory.get()) != nullptr);
}

TEST_CASE("Create StreamFigureFactory from STDIN") {
    AbstractFigureFactory& factory = AbstractFigureFactory::getInstance();
    auto figureFactory = factory.create("STDIN");

    REQUIRE(figureFactory != nullptr);
    REQUIRE(dynamic_cast<StreamFigureFactory*>(figureFactory.get()) != nullptr);
}

TEST_CASE("Invalid FigureFactory creation") {
    AbstractFigureFactory& factory = AbstractFigureFactory::getInstance();
    auto figureFactory = factory.create("InvalidType");

    REQUIRE(figureFactory == nullptr);
}

TEST_CASE("Create RandomFigureFactory and StreamFigureFactory sequentially") {
    AbstractFigureFactory& factory = AbstractFigureFactory::getInstance();

    // Create RandomFigureFactory
    auto randomFactory = factory.create("Random");
    REQUIRE(randomFactory != nullptr);
    REQUIRE(dynamic_cast<RandomFigureFactory*>(randomFactory.get()) != nullptr);

    // Create StreamFigureFactory from STDIN
    auto streamFactory = factory.create("STDIN");
    REQUIRE(streamFactory != nullptr);
    REQUIRE(dynamic_cast<StreamFigureFactory*>(streamFactory.get()) != nullptr);
}

TEST_CASE("Create StreamFigureFactory from File") {
    // Create a temporary file with valid data for a triangle
    std::ofstream tempFile("temp_test_file.txt");
    tempFile << "triangle 3 4 5\n";
    tempFile.close();

    // Test creating StreamFigureFactory from the temporary file
    std::ifstream ifs("temp_test_file.txt");
    StreamFigureFactory factory(ifs);
    auto figure = factory.create();

    REQUIRE(figure != nullptr);  // Ensure that the figure is created successfully
}

TEST_CASE("Create StreamFigureFactory from File and InvalidType sequentially") {
    // Create a temporary file with valid data for a triangle
    std::ofstream validFile("temp_valid_test_file.txt");
    validFile << "triangle 3 4 5\n";
    validFile.close();

    // Test creating StreamFigureFactory from the temporary file
    std::ifstream validIfs("temp_valid_test_file.txt");
    StreamFigureFactory validFactory(validIfs);
    auto validFigure = validFactory.create();

    REQUIRE(validFigure != nullptr);  // Ensure that the valid figure is created successfully

    // Create a separate file with invalid data
    std::ofstream invalidFile("temp_invalid_test_file.txt");
    invalidFile << "invalidType 1 2 3\n";  // Invalid type
    invalidFile.close();

    // Test creating StreamFigureFactory from the file with invalid data
    std::ifstream invalidIfs("temp_invalid_test_file.txt");
    StreamFigureFactory invalidFactory(invalidIfs);
    auto invalidFigure = invalidFactory.create();

    REQUIRE(invalidFigure == nullptr);  // Ensure that the invalid figure creation fails
}
