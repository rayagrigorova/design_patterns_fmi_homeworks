#include <fstream>

#include "AbstractFigureFactory.h"
#include "RandomFigureFactory.h"
#include "StreamFigureFactory.h"

std::unique_ptr<FigureFactory> AbstractFigureFactory::create(std::string str) {
	if (str == "Random") {
		return std::make_unique<RandomFigureFactory>();
	}
	if (str == "STDIN") {
		return std::make_unique<StreamFigureFactory>(std::cin);
	}
	if (str == "File") {
		std::cout << "Please, enter a file name: " << std::endl;
		std::string fileName;
		std::cin >> fileName;

		std::ifstream ifs(fileName);
		return std::make_unique<StreamFigureFactory>(ifs);
	}
	else {
		return nullptr;
	}
}
