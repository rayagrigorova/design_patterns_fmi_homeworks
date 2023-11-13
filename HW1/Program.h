#pragma once
#include <vector>

#include "AbstractFigureFactory.h"

class Program {
	std::vector<std::unique_ptr<Figure>> figures;

	bool init();

	void listToSTDOUT() const;
	void deleteFigure();
	void duplicateFigure();
	int saveToFile() const;
public:
	void run(); 
};