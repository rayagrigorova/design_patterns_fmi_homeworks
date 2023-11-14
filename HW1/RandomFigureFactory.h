#pragma once

#include "FigureFactory.h"
#include <random> 

const int numberOfShapes = 3;

enum class Shapes {
	triangle,
	circle,
	rectangle
};

class RandomFigureFactory : public FigureFactory {
	std::random_device rand_dev;
	std::mt19937 generator;

	const int range_from = 1;
	const int range_to = 10000;

	std::uniform_real_distribution<double>  distr;
	std::uniform_int_distribution<int>  typeDistr;


public:
	std::unique_ptr<Figure> create() override;
	RandomFigureFactory();
	RandomFigureFactory(int range_from, int range_to);
};