#pragma once

#include "Figure.h"

class Rectangle : public Figure {
	double a = 1;
	double b = 1;
public:
	Rectangle() = default;
	Rectangle(double a, double b);

	int perimeter() const override;
	std::unique_ptr<Figure> clone() const override;
	std::string toString() const override;
};