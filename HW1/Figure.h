#pragma once

#include <string>
#include <memory>

class Figure {
public:
	virtual int perimeter() const = 0;
	virtual std::unique_ptr<Figure> clone() const = 0;
	virtual std::string toString() const = 0;

	virtual ~Figure() = default;
};