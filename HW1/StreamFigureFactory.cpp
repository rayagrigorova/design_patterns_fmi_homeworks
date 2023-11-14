#include <iostream>
#include <stdexcept> 

#include "StreamFigureFactory.h"
#include "StringFigureFactory.h"

StreamFigureFactory::StreamFigureFactory(std::istream& is) : inputStream(is){

}

// TODO: create a move copy constructor 

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
