#include "catch2/catch_all.hpp"
#include "RandomFigureFactory.h"

TEST_CASE("Shapes distribution test") {
    const int numberOfShapes = 3;
    std::vector<int> observedCount(numberOfShapes, 0);
    const int totalSamples = 10000;

    RandomFigureFactory factory;

    for (int i = 0; i < totalSamples; ++i) {
        auto figure = factory.create();
        if (figure) {
            if (dynamic_cast<Triangle*>(figure.get())) {
                observedCount[0]++;
            } else if (dynamic_cast<Circle*>(figure.get())) {
                observedCount[1]++;
            } else if (dynamic_cast<Rectangle*>(figure.get())) {
                observedCount[2]++;
            }
        }
    }

    // Check if each shape count is within an acceptable range (e.g., within 10% of expected count)
    const int expectedCount = totalSamples / numberOfShapes;
    const double tolerance = 0.1;

    for (int i = 0; i < numberOfShapes; ++i) {
        double lowerBound = expectedCount * (1 - tolerance);
        double upperBound = expectedCount * (1 + tolerance);
        REQUIRE(observedCount[i] >= lowerBound);
        REQUIRE(observedCount[i] <= upperBound);
    }
}
