#include <iostream>

#include "Program.h"

void Program::init(){
	std::cout << "Choose how to enter a list of figures" << std::endl;
	std::string ans;
	std::cin >> ans;

	std::unique_ptr<FigureFactory> factory = AbstractFigureFactory().create(ans);
	
	if (ans == "Random" || ans == "STDIN") {
		int count = 0;
		std::cin >> count; 

		for (int i = 0; i < count; i++) {
			std::unique_ptr<Figure> fig = factory->create();
			figures.push_back(std::move(fig));
		}
	}

	else if (ans == "File") {
		while (1) {
			std::unique_ptr<Figure> fig = factory->create();
			if (!fig) {
				break;
			}
			figures.push_back(std::move(fig));
		}
	}
}
