#include <fstream>

#include "AbstractFigureFactory.h"
#include "RandomFigureFactory.h"
#include "StreamFigureFactory.h"

std::unique_ptr<FigureFactory> AbstractFigureFactory::create(const std::string& str) {
	if (str == "Random") {
		return std::make_unique<RandomFigureFactory>();
	}
	if (str == "STDIN") {
		return std::make_unique<StreamFigureFactory>(std::cin);
	}
	// TODO: the lines of code 15 to 28 are problematic 
	// They are causing a memoty leak. Solution: add a move copy constructor to StreamFigureFactory
	// and use it here 
	if (str == "File") {
		std::cout << "Please, enter a file name: " << std::endl;
		std::string fileName;
		std::cin >> fileName;

		std::ifstream* ifs = new std::ifstream(fileName);

		if (!ifs->is_open()) {
			std::cerr << "Error opening file: " << fileName << std::endl;
			delete ifs;
			return nullptr;
		}
		//rvalue ref
		return std::make_unique<StreamFigureFactory>(*ifs);
	}
	else {
		return nullptr;
	}
}
