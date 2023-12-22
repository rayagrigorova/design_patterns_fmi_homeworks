#pragma once

#include <iostream>
#include <optional>
#include <string>

#include "Labels.h"

// The 'service' in my implementation will be the SimpleLabel - it provides getText functionality and contains some text. 
// The proxy processes requests (getText() requests) and passes them to the service object. 
class STDINLabel : public Label {
	SimpleLabel label;
	size_t timeout; 
	// The number of calls is initially set to an invalid value to indicate that getText() hasn't been called yet 
	int numberOfCalls = -1;

	void enterText(); // a helper function to avoid code repetition 
public:
	STDINLabel(size_t timeout);
	std::string getText() override;
};