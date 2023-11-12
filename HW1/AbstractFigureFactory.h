#pragma once

#include <string>
#include <iostream>

#include "FigureFactory.h"

class AbstractFigureFactory : public FigureFactory{
public:
	virtual std::unique_ptr<FigureFactory> create(std::string str);
};

