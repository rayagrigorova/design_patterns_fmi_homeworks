#pragma once

#include <string>

class Figure {
public:
	virtual int perimeter() const = 0;
	virtual Figure* clone() const = 0;
	virtual std::string toString() const = 0;
};