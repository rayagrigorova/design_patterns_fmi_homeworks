#pragma once
#include <string>

// This class defines the common interface for both decorators 
// and components - the getText() function 
class Label {
public:
	// Should I make this method const? The random transformation decorator
	// has a random generator that should be changed each time getText() is called. 
	virtual std::string getText() { return ""; };
	virtual ~Label() = default;
	virtual bool operator==(const Label& other) const = 0;
};

class SimpleLabel : public Label {
public:
	std::string value;

	SimpleLabel(std::string value) : value(value){}
	
	std::string getText() override {
		return value;
	}

	virtual bool operator==(const Label& other) const {
		
	}
};

// This class should store text as well as some additional info
class RichLabel : public SimpleLabel {
public:
	// Should I use the bridge pattern here? It sounds like overkill
	std::string color, font;
	size_t fontSize;

	RichLabel(std::string value, std::string color, std::string font, size_t fontSize) : SimpleLabel(value), color(color), font(font), fontSize(fontSize){}
};