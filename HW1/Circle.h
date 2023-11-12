#pragma once

#include "Figure.h"

class Circle : public Figure {
	double r = 1;
public:
	Circle() = default;
	Circle(double r);

	int perimeter() const override;
	std::unique_ptr<Figure> clone() const override;
	std::string toString() const override;
};