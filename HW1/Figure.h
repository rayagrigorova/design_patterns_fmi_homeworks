#pragma once

#include <string>
#include <memory>

// TODO: don't calculate perimeter and toString every time, initialize them in the constructor 
// and make them class members 

// Also, put all figures in one .h file  and one .cpp file so that they are compactly put together 
class Figure {
public:
	virtual int perimeter() const = 0;
	virtual std::unique_ptr<Figure> clone() const = 0;
	virtual std::string toString() const = 0;

	virtual ~Figure() = default;
};