#include "Labels.h"

std::string Label::getText() {
	return "";
}

SimpleLabel::SimpleLabel() : value("") {

}

SimpleLabel::SimpleLabel(const std::string& value) : value(value) {

}

Label* SimpleLabel::clone() const {
	return new SimpleLabel(this->value);
}

std::string SimpleLabel::getText() {
	return value;
}


RichLabel::RichLabel(const std::string& value, const std::string& color, const std::string& font, size_t fontSize) 
	: SimpleLabel(value), color(color), font(font), fontSize(fontSize) {

}

RichLabel::RichLabel(const RichLabel& other) 
	: SimpleLabel(other.value), color(other.color), font(other.font), fontSize(other.fontSize) {

}

Label* RichLabel::clone() const {
	return new RichLabel(*this);
}