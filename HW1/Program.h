#pragma once
#include <vector>

#include "AbstractFigureFactory.h"

class Program {
	std::vector<std::unique_ptr<Figure>> figures;
public:
	void init();
	void listToSTDOUT() const;
	void deleteFigure(int ind);
	void cloneFigure(int ind);
	void saveToFile() const;
};