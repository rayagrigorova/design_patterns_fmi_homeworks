#include "Rectangle.h"

#include <stdexcept> // std::invalid_argument

Rectangle::Rectangle(double a, double b) {
	if (a <= 0 || b <= 0) {
		throw std::invalid_argument("Invalid rectangle sides");
	}

	// For consistency with the triangle class, a <= b 
	this->a = std::min(a, b);
	this->b = std::max(a, b);
}

int Rectangle::perimeter() const {
	return 2 * (a + b);
}

std::unique_ptr<Figure> Rectangle::clone()  const {
	return std::make_unique<Rectangle>(*this);
}

std::string Rectangle::toString() const {
	return "rectangle " + std::to_string(a) + " " + std::to_string(b);
}
