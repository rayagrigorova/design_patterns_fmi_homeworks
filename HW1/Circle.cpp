#include "Circle.h"

// pi
#define _USE_MATH_DEFINES
#include <math.h> 

#include <stdexcept> // std::invalid_argument

Circle::Circle(double r) {
    if (r <= 0) {
        throw std::invalid_argument("Invalid radius");
    }
    this->r = r;
}

int Circle::perimeter() const {
    return 2 * M_PI * r;
}

Figure* Circle::clone() const {
    return new Circle(*this);
}

std::string Circle::toString() const {
    return "circle " + std::to_string(r);
}
