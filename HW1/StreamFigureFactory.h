#pragma once

#include "FigureFactory.h"

class StreamFigureFactory : public FigureFactory {
	std::istream& inputStream;

public:
	StreamFigureFactory(std::istream& is);
	StreamFigureFactory(std::istream&& is) noexcept;
	std::unique_ptr<Figure> create() override;

	static std::unique_ptr<Figure> createFigure(std::istream& is);

};