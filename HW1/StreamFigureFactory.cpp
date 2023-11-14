#include <iostream>
#include <stdexcept> 

#include "StreamFigureFactory.h"
#include "StringFigureFactory.h"

#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"

StreamFigureFactory::StreamFigureFactory(std::istream& is) : inputStream(is){

}

// TODO: create a move copy constructor 
StreamFigureFactory::StreamFigureFactory(std::istream&& is) noexcept : inputStream(std::move(is)) {

}

std::unique_ptr<Figure> StreamFigureFactory::create() {
    if (!inputStream) {
        std::cerr << "Input stream is not okay for reading." << std::endl;
        return nullptr;
    }
    try {
        std::string data;
        if (std::getline(inputStream, data)) {
            return StringFigureFactory(data).create();
        }
        else {
            return nullptr;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return nullptr;
    }
}

// Helper functions to create shape from a line in an input stream 
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

std::unique_ptr<Figure> StreamFigureFactory::createFigure(std::istream& is) {
    std::string type;
    is >> type;

    if (type == "triangle") {
        return createTriangle(is);
    }
    if (type == "circle") {
        return createCircle(is);
    }
    if (type == "rectangle") {
        return createRectangle(is);
    }
    return nullptr;
}
