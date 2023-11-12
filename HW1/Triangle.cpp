#include "Triangle.h"

#include <stdexcept> // std::invalid_argument
#include <algorithm> // std::sort

bool isValidTriangle(double a, double b, double c) {
	return (a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a);
}

Triangle::Triangle(double a, double b, double c){
	if (!isValidTriangle(a, b, c)) {
		throw std::invalid_argument("Invalid values for triangle sides");
	}

	// Make sure that a <= b <= c
	double sides[] = { a, b, c };
	std::sort(std::begin(sides), std::end(sides));

	this->a = sides[0];
	this->b = sides[1];
	this->c = sides[2];
}

int Triangle::perimeter() const {
	return a + b + c;
}

std::unique_ptr<Figure> Triangle::clone() const{
	return std::make_unique<Triangle>(*this);
}

std::string Triangle::toString() const {
	return "triangle " + std::to_string(a) + " " + std::to_string(b) + " " + std::to_string(c); 
}


