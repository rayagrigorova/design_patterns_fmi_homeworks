#pragma once

#include "FigureFactory.h"

#include <sstream>

class StringFigureFactory : public FigureFactory {
	std::stringstream ss;
public:
	StringFigureFactory();
	StringFigureFactory(std::string str);
	virtual std::unique_ptr<Figure> create() override;
};