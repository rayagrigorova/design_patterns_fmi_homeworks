#pragma once

#include <string>
#include <iostream>

#include "FigureFactory.h"

// TODO: make the AbstractFigureFactory class singleton and call getInstance() to it 

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

