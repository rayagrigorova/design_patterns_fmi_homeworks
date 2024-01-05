#pragma once

#include <string>

// This class defines the common interface for both decorators 
// and components - the getText() function 
class Label {
public:
	virtual std::string getText() { return ""; };
	virtual ~Label() = default;
	virtual Label* clone() const = 0;
};

class SimpleLabel : public Label {
public:
	std::string value;

	SimpleLabel() : value(""){}
	SimpleLabel(const std::string& value) : value(value){}

	virtual Label* clone() const override {
		return new SimpleLabel(this->value);
	}
	
	std::string getText() override {
		return value;
	}
};

class RichLabel : public SimpleLabel {
public:
	std::string color, font;
	size_t fontSize;

	RichLabel(const std::string& value,const std::string& color, const std::string& font, size_t fontSize) : SimpleLabel(value), color(color), font(font), fontSize(fontSize){}
	RichLabel(const RichLabel& other) : SimpleLabel(other.value), color(other.color), font(other.font), fontSize(other.fontSize){}

	virtual Label* clone() const override {
		return new RichLabel(*this); 
	}
};