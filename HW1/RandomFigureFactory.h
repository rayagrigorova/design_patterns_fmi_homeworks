#pragma once

#include "FigureFactory.h"
#include <random> 

class RandomFigureFactory : public FigureFactory {
	std::random_device randDev;
	std::mt19937 generator;

	const int rangeFrom;
	const int rangeTo;

	std::uniform_real_distribution<double>  distr;
	std::uniform_int_distribution<int>  typeDistr;

public:
	std::unique_ptr<Figure> create() override;
	RandomFigureFactory();
	RandomFigureFactory(int rangeFrom, int rangeTo);
};