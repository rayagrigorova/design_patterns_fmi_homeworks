#pragma once

#include <string>

// This class defines the common interface for both decorators 
// and components - the getText() function 
class Label {
public:
	virtual std::string getText();
	virtual ~Label() = default;
	virtual Label* clone() const = 0;
};

class SimpleLabel : public Label {
public:
	std::string value;

	SimpleLabel();
	SimpleLabel(const std::string& value);

	virtual Label* clone() const override;
	
	std::string getText() override;
};

class RichLabel : public SimpleLabel {
public:
	std::string color, font;
	size_t fontSize;

	RichLabel(const std::string& value, const std::string& color, const std::string& font, size_t fontSize);
	RichLabel(const RichLabel& other);

	virtual Label* clone() const override;
};