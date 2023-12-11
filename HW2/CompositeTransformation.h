#pragma once

#include <vector>
#include <memory>

#include "Labels.h"

// What class should CompositeTransformation inherit from?
// The SimpleLabel class has a text field, should I inherit from it?
class CompositeTransformation : public Label{
	std::vector<std::unique_ptr<Label>> children;
	std::string text;
public:
	CompositeTransformation(const std::string& text);

	void add(const Label& l);
	void add(Label&& l);

	void remove(const Label& l);

	virtual std::string getText() override;
};