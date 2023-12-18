#pragma once
#include <string>

// This class defines the common interface for both decorators 
// and components - the getText() function 
class Label {
public:
	// Should I make this method const? 
	// The random transformation decorator
	// has a random generator that should be changed
	// each time getText() is called. 
	virtual std::string getText() { return ""; };
	virtual ~Label() = default;

	// Should the '==' function be virtual and in the base class 'Label'?
	virtual bool operator==(const Label& other) const { return false; }
};

class SimpleLabel : public Label {
public:
	std::string value;

	SimpleLabel(std::string value) : value(value){}
	
	std::string getText() override {
		return value;
	}

	bool operator==(const Label& other) const override {
		const SimpleLabel* otherPtr = dynamic_cast<const SimpleLabel*>(&other);
		if (!otherPtr) {
			return false;
		}

		return value == otherPtr->value;
	}
};

class RichLabel : public SimpleLabel {
public:
	std::string color, font;
	size_t fontSize;

	RichLabel(std::string value, std::string color, std::string font, size_t fontSize) : SimpleLabel(value), color(color), font(font), fontSize(fontSize){}

	bool operator==(const Label& other) const override {
		const RichLabel* otherPtr = dynamic_cast<const RichLabel*>(&other);
		if (!otherPtr) {
			return false;
		}

		return (SimpleLabel::operator==(*otherPtr) && color == otherPtr->color
			&& font == otherPtr->font && fontSize == otherPtr->fontSize);
	}
};