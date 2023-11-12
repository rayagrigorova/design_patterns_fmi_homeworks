#include "Triangle.h"

#include <stdexcept> // std::invalid_argument
#include <algorithm> // std::sort

Triangle::Triangle(double a, double b, double c){
	// Make sure that a <= b <= c
	double sides[] = { a, b, c };
	std::sort(std::begin(sides), std::end(sides));

	// Only check if the first side is <= 0 since it is the smallest one.
	// Given that all sides are positive numbers, the check sides[0] + sides[1] <= sides[2]
	// is enough since sides[1] + sides[2] <= sides[0] is impossible, as well as sides[2] + sides[0] <= sides[1]
	if (sides[0] <= 0 || sides[0] + sides[1] <= sides[2]) {
		throw std::invalid_argument("Invalid values for triangle sides");
	}

	this->a = sides[0];
	this->b = sides[1];
	this->c = sides[2];
}

int Triangle::perimeter() const {
	return a + b + c;
}

Figure* Triangle::clone() const{
	return new Triangle(*this);
}

std::string Triangle::toString() const {
	return "triangle " + std::to_string(a) + " " + std::to_string(b) + " " + std::to_string(c); 
}
