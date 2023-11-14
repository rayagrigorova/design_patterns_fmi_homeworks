#pragma once

#include <string>
#include <memory>

// I have put all figures in one class since the code for them is short.
// My intention is to increase code readability. 

// I am going to add the perimeter and string representation of shapes as class members
// This way, they will not be recalculated each time perimeter() and toString() are called 
class Figure {
protected:
	// Functions to get perimeter and string representation will be different for all shapes 
	virtual void calculatePerimeter() = 0;
	virtual void calculateString() = 0;

	double per = 0;
	std::string str = "";
public:
	virtual std::unique_ptr<Figure> clone() const = 0;

	double perimeter() const;
	const std::string& toString() const;

	virtual ~Figure() = default;
};

class Circle : public Figure {
	double r;

protected:
	virtual void calculatePerimeter() override;
	virtual void calculateString() override;

public:
	Circle();
	Circle(double r);

	std::unique_ptr<Figure> clone() const override;
};

class Rectangle : public Figure {
	double a, b;

protected:
	virtual void calculatePerimeter() override;
	virtual void calculateString() override;

public:
	Rectangle();
	Rectangle(double a, double b);

	std::unique_ptr<Figure> clone() const override;
};

class Triangle : public Figure {
	double a, b, c;

protected:
	virtual void calculatePerimeter() override;
	virtual void calculateString() override;

public:
	Triangle();
	Triangle(double a, double b, double c);

	std::unique_ptr<Figure> clone() const override;
};
bool isValidTriangle(double a, double b, double c);