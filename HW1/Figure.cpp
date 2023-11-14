// pi
#define _USE_MATH_DEFINES
#include <math.h> 

#include <stdexcept> // std::invalid_argument
#include <algorithm> // std::sort

#include "Figure.h"

double Figure::perimeter() const {
	return per;
}

const std::string& Figure::toString() const {
	return str;
}

Circle::Circle(double r) {
    if (r <= 0) {
        throw std::invalid_argument("Invalid radius");
    }
    this->r = r;

	calculatePerimeter();
	calculateString();
}

void Circle::calculatePerimeter() {
	per = 2 * M_PI * r;
}

void Circle::calculateString() {
	str += "circle";
	str += std::to_string(r);
}

Circle::Circle(){
	r = 1;

	calculatePerimeter();
	calculateString();
}

std::unique_ptr<Figure> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

Rectangle::Rectangle(double a, double b) {
	if (a <= 0 || b <= 0) {
		throw std::invalid_argument("Invalid rectangle sides");
	}

	// For consistency with the triangle class, a <= b 
	this->a = std::min(a, b);
	this->b = std::max(a, b);

	calculatePerimeter();
	calculateString();
}

Rectangle::Rectangle() {
	a = 1;
	b = 1;

	calculatePerimeter();
	calculateString();
}

void Rectangle::calculatePerimeter() {
	per = 2 * (a + b); 
}

void Rectangle::calculateString() {
	str += "rectangle ";
	str += std::to_string(a);
	str += " ";
	str += std::to_string(b);
}

std::unique_ptr<Figure> Rectangle::clone()  const {
	return std::make_unique<Rectangle>(*this);
}

bool isValidTriangle(double a, double b, double c) {
	return (a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a);
}

Triangle::Triangle() {
	a = 1;
	b = 1;
	c = 1;

	calculatePerimeter();
	calculateString();
}

Triangle::Triangle(double a, double b, double c) {
	if (!isValidTriangle(a, b, c)) {
		throw std::invalid_argument("Invalid values for triangle sides");
	}

	// Make sure that a <= b <= c
	double sides[] = { a, b, c };
	std::sort(std::begin(sides), std::end(sides));

	this->a = sides[0];
	this->b = sides[1];
	this->c = sides[2];

	calculatePerimeter();
	calculateString();
}

void Triangle::calculatePerimeter() {
	per = a + b + c;
}
void Triangle::calculateString() {
	str += "triangle ";
	str += std::to_string(a);
	str += " ";
	str += std::to_string(b);
	str += " ";
	str += std::to_string(c);
}

std::unique_ptr<Figure> Triangle::clone() const {
	return std::make_unique<Triangle>(*this);
}

