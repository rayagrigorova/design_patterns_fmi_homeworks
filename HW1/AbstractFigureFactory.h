#pragma once

#include <string>
#include <iostream>

#include "FigureFactory.h"

// TODO: make the AbstractFigureFactory class singleton and call getInstance() to it 

class AbstractFigureFactory {
public:
	virtual std::unique_ptr<FigureFactory> create(const std::string& str);
};

