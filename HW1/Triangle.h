#pragma once

#include "Figure.h"

class Triangle : public Figure {
	double a = 1, b = 1, c = 1;
public: 
	Triangle() = default;
	Triangle(double a, double b, double c);

	int perimeter() const override;
	Figure* clone() const override;
	std::string toString() const override;
};