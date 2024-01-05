#include "InteractiveLabelCreation.h"

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

TextTransformationDecorator addTransformation(Label& label, const TextTransformation& t) {
	return TextTransformationDecorator(label, t);
}

RandomTransformationDecorator addRandomTransformationDecorator(Label& label,
	std::vector<std::unique_ptr<TextTransformation>>&& transformations) {
	return RandomTransformationDecorator(label, std::move(transformations));
}