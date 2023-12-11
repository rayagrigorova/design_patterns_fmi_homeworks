#include "STDINLabel.h"

std::string STDINLabel::getText() {
	if (text.has_value()) {
		return text.value();
	}

	std::string input;
	std::cout << "Enter a string\n";
	std::getline(std::cin, input);

	text = input;
	return text.value();
}