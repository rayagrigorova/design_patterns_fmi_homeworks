#pragma once

#include <fstream>

#include "FigureFactory.h"

class StreamFigureFactory : public FigureFactory {
	std::ifstream file; 
	std::istream& inputStream;

public:
	StreamFigureFactory(std::istream& is);
	StreamFigureFactory(std::ifstream&& ifs);
	std::unique_ptr<Figure> create() override;

	static std::unique_ptr<Figure> createFigure(std::istream& is);
};