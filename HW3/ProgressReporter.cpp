#include <iostream>
#include <chrono>
#include <thread> 

#include "ProgressReporter.h"

void ProgressReporter::update(const std::string& context) const {
	std::cout << "Processing " << context << "...\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(250));
}
