#include <stdexcept>
#include <iostream>

#include "StringFigureFactory.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"

StringFigureFactory::StringFigureFactory() : ss("") {

}

StringFigureFactory::StringFigureFactory(std::string str) : ss(std::move(str)){

}

// TODO: read the data from a stream, not from a string stream
// Define the methods from the namespace as private class methods 
namespace {
    std::unique_ptr<Figure> createTriangle(std::istream& is) {
        double a, b, c;
        is >> a >> b >> c;
        return std::make_unique<Triangle>(a, b, c);
    }

    std::unique_ptr<Figure> createCircle(std::istream& is) {
        double r;
        is >> r;
        return std::make_unique<Circle>(r);
    }

    std::unique_ptr<Figure> createRectangle(std::istream& is) {
        double a, b;
        is >> a >> b;
        return std::make_unique<Rectangle>(a, b);
    }
}

// Create figure from string representation 
std::unique_ptr<Figure> StringFigureFactory::create() {
    if (!ss) {
        return nullptr;
        /*throw std::invalid_argument("String already read");*/
    }

    try {
        std::string type;
        ss >> type;

        if (type == "triangle") {
            return createTriangle(ss);
        }
        if (type == "circle") {
            return createCircle(ss);
        }
        if (type == "rectangle") {
            return createRectangle(ss);
        }
        /*throw std::invalid_argument("Invalid shape type");*/
        return nullptr;
    }

    catch (std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Stream failure: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
