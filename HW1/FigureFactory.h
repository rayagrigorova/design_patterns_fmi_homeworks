#pragma once

#include "Figure.h"

class FigureFactory {
public:
	virtual std::unique_ptr<Figure> create() = 0;
};