#include <stdexcept>
#include <iostream>

#include "StringFigureFactory.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"

#include "StreamFigureFactory.h"

#include <sstream>

StringFigureFactory::StringFigureFactory() : s("") {

}

StringFigureFactory::StringFigureFactory(std::string str) : s(std::move(str)){

}

// Create figure from string representation 
std::unique_ptr<Figure> StringFigureFactory::create() {

    try {
        std::stringstream ss(s);
        return StreamFigureFactory::createFigure(ss);
    }

    catch (std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return nullptr;
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Stream failure: " << e.what() << std::endl;
        return nullptr;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return nullptr;
    }
}
