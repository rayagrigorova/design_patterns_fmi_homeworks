#include <stdexcept>
#include <iostream>

#include "StringFigureFactory.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"

StringFigureFactory::StringFigureFactory() : ss("") {

}

StringFigureFactory::StringFigureFactory(std::string str) : ss(str){

}

namespace {
    // Functions to be used in StringFigureFactory's create()
    std::unique_ptr<Figure> createTriangle(std::stringstream& ss) {
        double a, b, c;
        ss >> a >> b >> c;
        return std::make_unique<Triangle>(a, b, c);
    }

    std::unique_ptr<Figure> createCircle(std::stringstream& ss) {
        double r;
        ss >> r;
        return std::make_unique<Circle>(r);
    }

    std::unique_ptr<Figure> createRectangle(std::stringstream& ss) {
        double a, b;
        ss >> a >> b;
        return std::make_unique<Rectangle>(a, b);
    }
}

// Create figure from string representation 
std::unique_ptr<Figure> StringFigureFactory::create() {
    if (!ss) {
        throw std::invalid_argument("String already read");
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
        throw std::invalid_argument("Invalid shape type");
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
