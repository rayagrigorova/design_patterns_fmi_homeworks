#pragma once

#include "Labels.h"
#include "LabelDecorators.h"
#include "Transformations.h"
#include "SimpleHelpLabel.h"
#include "STDINLabel.h"

// This file contains functions that allow the user to 
// interactively create labels with different combinations of features 

// All of the functions below act as specialized factory methods for creating labels with specific features.

// The type of dependency injection I am using is constructor injection
// (the dependencies are provided through a class constructor)

SimpleLabel createSimpleLabel(const std::string& value) {
	return SimpleLabel(value);
}

RichLabel createRichLabel(const std::string& value, const std::string& color,
	const std::string& font, size_t fontSize) {
	return RichLabel(value, color, font, fontSize);
}

STDINLabel createSTDINLabel(size_t timeout) {
	return STDINLabel(timeout);
}

SimpleHelpLabel addHelpText(Label& label, const std::string& helpText) {
	return SimpleHelpLabel(label, helpText);
}

TextTransformationDecorator addTransformation(Label* label, const TextTransformation& t) {
	return TextTransformationDecorator(label, t);
}

RandomTransformationDecorator addRandomTransformationDecorator(Label* label,
	std::vector<std::unique_ptr<TextTransformation>>&& transformations) {
	return RandomTransformationDecorator(label, std::move(transformations));
}


