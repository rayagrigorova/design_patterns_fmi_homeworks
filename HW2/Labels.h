#pragma once
#include <string>

// This class defines the common interface for both decorators 
// and components - the getText() function 
class Label {
public:
	virtual std::string getText() { return ""; };
	virtual ~Label() = default;
};

class SimpleLabel : public Label {
public:
	std::string value;

	SimpleLabel(std::string value) : value(value){}
	
	std::string getText() override {
		return value;
	}
};

class RichLabel : public SimpleLabel {
public:
	std::string color, font;
	size_t fontSize;

	RichLabel(std::string value, std::string color, std::string font, size_t fontSize) : SimpleLabel(value), color(color), font(font), fontSize(fontSize){}
};