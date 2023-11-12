#pragma once

#include "FigureFactory.h"

class StreamFigureFactory : public FigureFactory {
	std::istream& inputStream;

public:
	StreamFigureFactory(std::istream& is);
	std::unique_ptr<Figure> create() override;
};