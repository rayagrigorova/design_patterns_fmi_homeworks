#include <random>

#include "RandomFigureFactory.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"

const int TRIANGLE_TYPE = 0;
const int CIRCLE_TYPE = 1;
const int RECTANGLE_TYPE = 2;

namespace {
    // Functions to be used in StringFigureFactory's create()
    std::unique_ptr<Figure> createTriangle(std::uniform_real_distribution<double>&  distr, std::mt19937& generator) {
        double a, b, c;
        do {
            a = distr(generator);
            b = distr(generator);
            c = distr(generator);
        } while (!isValidTriangle(a, b, c));

        return std::make_unique<Triangle>(a, b, c);
    }

    std::unique_ptr<Figure> createCircle(std::uniform_real_distribution<double>& distr, std::mt19937& generator) {
        double r = distr(generator);

        return std::make_unique<Circle>(r);
    }

    std::unique_ptr<Figure> createRectangle(std::uniform_real_distribution<double>& distr, std::mt19937& generator) {
        double a = distr(generator);
        double b = distr(generator);

        return std::make_unique<Rectangle>(a, b);
    }
}

std::unique_ptr<Figure> RandomFigureFactory::create() {
    const int range_from = 1;
    const int range_to = 10000;
    const int numberOfShapes = 3;

    std::uniform_real_distribution<double>  distr(range_from, range_to);
    std::uniform_int_distribution<int>  typeDistr(0, numberOfShapes - 1);

    int type = typeDistr(generator);

    switch (type) {
    case TRIANGLE_TYPE:
        return createTriangle(distr, generator);
    case CIRCLE_TYPE: 
        return createCircle(distr, generator);
    case RECTANGLE_TYPE:
        return createRectangle(distr, generator);
    }
}

RandomFigureFactory::RandomFigureFactory() : rand_dev(), generator(rand_dev()) {
}
