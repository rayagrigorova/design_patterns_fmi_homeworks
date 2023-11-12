#pragma once

#include "FigureFactory.h"

class RandomFigureFactory : public FigureFactory {
	std::random_device rand_dev;
	std::mt19937 generator;
public:
	std::unique_ptr<Figure> create() override;
	RandomFigureFactory();
};