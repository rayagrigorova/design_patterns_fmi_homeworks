#include <cassert>

#include "RandomFigureFactory.h"
#include "Figure.h"

const int numberOfShapes = 3;

enum class Shapes {
    triangle,
    circle,
    rectangle
};

namespace {
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
    int type = typeDistr(generator);

    switch (type) {
    case static_cast<int>(Shapes::triangle):
        return createTriangle(distr, generator);
    case static_cast<int>(Shapes::circle):
        return createCircle(distr, generator);
    case static_cast<int>(Shapes::rectangle):
        return createRectangle(distr, generator);
    }
    assert(false);
    return nullptr;
}

RandomFigureFactory::RandomFigureFactory() : randDev(), generator(randDev()), rangeFrom(1), rangeTo(10000),
                                             distr(rangeFrom, rangeTo), typeDistr(0, numberOfShapes - 1){
}

RandomFigureFactory::RandomFigureFactory(int rangeFrom, int rangeTo) : randDev(), generator(randDev()), rangeFrom(rangeFrom), rangeTo(rangeTo),
                                                                         distr(rangeFrom, rangeTo), typeDistr(0, numberOfShapes - 1) {
}
