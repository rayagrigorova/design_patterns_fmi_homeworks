#include <iostream>
#include <fstream>

#include "Program.h"

bool Program::init(){
	std::cout << "Choose how to enter a list of figures" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "Random, STDIN, File" << std::endl;
	std::string ans;
	std::cin >> ans;

	std::unique_ptr<FigureFactory> factory = AbstractFigureFactory::getInstance().create(ans);
	
	if (ans == "Random" || ans == "STDIN") {
		std::cout << "Please, enter the number of figures to generate" << std::endl;
		int count = 0;
		std::cin >> count; 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (count < 0) {
			std::cerr << "The number of figures entered is invalid";
			return false;
		}

		// request that the vector capacity be at least enough to contain (figures.size() + count) elements
		figures.reserve(figures.size() + count);

		for (int i = 0; i < count; i++) {
			std::unique_ptr<Figure> fig = factory->create();
			figures.emplace_back(std::move(fig));
		}
		return true;
	}

	else if (ans == "File") {
		while (1) {
			std::unique_ptr<Figure> fig = factory->create();
			if (!fig) {
				break;
			}
			figures.push_back(std::move(fig));
		}
		return true;
	}
	else {
		return false;
	}
}

void Program::listToSTDOUT() const {
	if (figures.size() == 0) {
		std::cout << "The list of figures is empty" << std::endl;
		return;
	}

	for (int i = 0; i < figures.size(); i++) {
		std::cout << i << ". ";
		std::cout << figures[i]->toString() << std::endl;
	}
	std::cout << std::endl;
}

void Program::deleteFigure() {
	std::cout << "Please enter an index" << std::endl;
	int ind;
	std::cin >> ind;

	if (ind < 0 || ind >= figures.size()) {
		std::cerr << "The delete index is invalid" << std::endl;
		return;
	}

	figures.erase(figures.begin() + ind);
}

void Program::duplicateFigure() {
	std::cout << "Please enter an index" << std::endl;
	int ind;
	std::cin >> ind;

	if (ind < 0 || ind >= figures.size()) {
		std::cerr << "The duplicate index is invalid" << std::endl;
		return;
	}
	figures.push_back(figures[ind]->clone());
}

int Program::saveToFile() const {
	std::cout << "Please enter the name of the file" << std::endl;
	std::string filename;
	std::cin >> filename;

	std::ofstream ofs(filename);
	if (!ofs.is_open()) {
		std::cerr << "Error opening the file!" << std::endl;
		return 1;
	}

	// Each line is one figure
	for (int i = 0; i < figures.size(); i++) {
		ofs << figures[i]->toString() << std::endl;
	}

	ofs.close();
	std::cout << "Successfully saved to file" << std::endl;
	return 0;
}

void Program::run() {
	// If the initialization fails, the program will not run
	if (!init()) {
		return;
	}

	bool flag = true;
	do {
		char ch;
		std::cout << "Please, enter a command" << std::endl;
		std::cout << "\'l\': list figures to STDOUT" << std::endl;
		std::cout << "\'d\': delete a figure at a given index" << std::endl;
		std::cout << "\'c\': clone a figure at a given index" << std::endl;
		std::cout << "\'s\': save figures to file" << std::endl;
		std::cout << "\'x\': to exit the program" << std::endl;
		std::cin >> ch;

		switch (ch) {
		case 'l' : 
			listToSTDOUT();
			break;
		case 'd': 
			deleteFigure();
			break;
		case 'c':
			duplicateFigure();
			break;
		case 's': 
			saveToFile();
			break;
		case 'x':
			flag = false;
			break;
		default:
			std::cout << "The command you have entered is invalid" << std::endl;
		}
	} while (flag);
}
