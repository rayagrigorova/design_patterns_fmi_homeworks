#pragma once

#include "FigureFactory.h"

class StringFigureFactory : public FigureFactory {
	std::string s;
public:
	StringFigureFactory();
	StringFigureFactory(std::string str);
	virtual std::unique_ptr<Figure> create() override;
};