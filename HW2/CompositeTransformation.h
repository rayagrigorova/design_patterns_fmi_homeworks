#pragma once

#include <vector>
#include <memory>

#include "Transformations.h"
#include "Labels.h"

// "This class will allow for a sequence of transformations to be treated as a single transformation"
// The common interface for all transformations is TextTransformation, so inherit from it 
class CompositeTransformation : public TextTransformation{
	std::vector<std::unique_ptr<TextTransformation>> children;
public:
	CompositeTransformation(std::vector<std::unique_ptr<TextTransformation>>&& children);

	void add(std::unique_ptr<TextTransformation>&& tt);
	void remove(const TextTransformation& tt);

	virtual std::string transform(std::string text) const override;
	bool equals(const TextTransformation& other) const override;
};