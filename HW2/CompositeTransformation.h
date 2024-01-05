#pragma once

#include <vector>
#include <memory>

#include "Transformations.h"
#include "Labels.h"

class CompositeTransformation : public TextTransformation{
	std::vector<std::unique_ptr<TextTransformation>> children;
public:
	CompositeTransformation() = default;
	CompositeTransformation(std::vector<std::unique_ptr<TextTransformation>>&& children) noexcept;

	void add(std::unique_ptr<TextTransformation>&& tt);
	void remove(const TextTransformation& tt);

	virtual std::string transform(std::string text) const override;
	bool equals(const TextTransformation& other) const override;

	virtual std::unique_ptr<TextTransformation> clone() const override;
};