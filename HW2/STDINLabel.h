#pragma once

#include <iostream>
#include <optional>
#include <string>

#include "Labels.h"

// What is the service supposed to be?
// Also, what is the 'timeout' option supposed to be?
class STDINLabel : public Label {
	std::optional<std::string> text;
public:
	std::string getText() override;
};