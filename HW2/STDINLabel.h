#pragma once

#include <iostream>
#include <optional>
#include <string>

#include "Labels.h"

// TODO: StreamLabel instead of stdin label for a better level of abstraction 

class STDINLabel : public Label {
	// TODO: keep reference to isteram object 
	// for unit tests: use a string stream 
	std::optional<std::string> text;
public:
	// TIMEOUT: number of times to request the text before entering again 
	// parameter in constructor 
	std::string getText() override;
};