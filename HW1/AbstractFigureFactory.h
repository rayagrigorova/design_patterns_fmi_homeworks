#pragma once

#include <string>
#include <iostream>

#include "FigureFactory.h"

class AbstractFigureFactory {
protected:
	AbstractFigureFactory() = default;
	~AbstractFigureFactory() = default;

public:
	virtual std::unique_ptr<FigureFactory> create(const std::string& str);

	static AbstractFigureFactory& getInstance();

	// Delete all methods that could enable copying 
	AbstractFigureFactory(const AbstractFigureFactory&) = delete;
	AbstractFigureFactory(AbstractFigureFactory&&) = delete;

	AbstractFigureFactory& operator=(const AbstractFigureFactory&) = delete;
	AbstractFigureFactory& operator=(AbstractFigureFactory&&) = delete;
};

