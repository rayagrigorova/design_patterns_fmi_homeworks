#pragma once

#include "Labels.h"
#include "LabelDecorators.h"
#include "Transformations.h"
#include "SimpleHelpLabel.h"
#include "STDINLabel.h"

SimpleLabel createSimpleLabel(const std::string& value);

RichLabel createRichLabel(const std::string& value, const std::string& color, const std::string& font, size_t fontSize);

STDINLabel createSTDINLabel(size_t timeout);

SimpleHelpLabel addHelpText(Label& label, const std::string& helpText); 

TextTransformationDecorator addTransformation(Label& label, const TextTransformation& t); 

RandomTransformationDecorator addRandomTransformationDecorator(Label& label,
	std::vector<std::unique_ptr<TextTransformation>>&& transformations); 


