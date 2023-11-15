#include <stdexcept>
#include <iostream>

#include "StringFigureFactory.h"
#include "Figure.h"

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

    catch (const std::ios_base::failure& e) {
        std::cerr << "Stream failure: " << e.what() << std::endl;
        return nullptr;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return nullptr;
    }
}
