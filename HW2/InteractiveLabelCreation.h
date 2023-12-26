#pragma once

#include "Labels.h"
#include "LabelDecorators.h"
#include "Transformations.h"
#include "SimpleHelpLabel.h"
#include "STDINLabel.h"

// This file contains functions that allow the user to 
// interactively create labels with different combinations of features
// Each of the  functions return a reference to a unique pointer, which allows applying them one after another. 

// All of the functions below act as specialized factory methods for creating labels with specific features.
// This is done to avoid requesting input from cin constantly.

// The type of dependency injection I am using is constructor injection
// (the dependencies are provided through a class constructor)

std::unique_ptr<Label> createSimpleLabel(const std::string& value) {
	return std::make_unique<SimpleLabel>(value);
}

std::unique_ptr<Label> createRichLabel(const std::string& value, const std::string& color, 
	const std::string& font, size_t fontSize) {
	return std::make_unique<RichLabel>(value, color, font, fontSize);
}

std::unique_ptr<Label> createSTDINLabel(size_t timeout) {
	return std::make_unique<STDINLabel>(timeout);
}

std::unique_ptr<Label> addHelpText(std::unique_ptr<Label> label, const std::string& helpText) {
	return std::make_unique<SimpleHelpLabel>(*label, helpText);
}

std::unique_ptr<Label> addTransformation(std::unique_ptr<Label> label, TextTransformation& t) {
	return std::make_unique<TextTransformationDecorator>(label.release(), t);
}

std::unique_ptr<Label> addRandomTransformationDecorator(std::unique_ptr<Label> label, 
	std::vector<std::unique_ptr<TextTransformation>>&& transformations) {
	return std::make_unique<RandomTransformationDecorator>(label.release(), std::move(transformations));
}


