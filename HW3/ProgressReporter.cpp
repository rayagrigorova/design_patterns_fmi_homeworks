#include <iostream>
#include <chrono>
#include <thread> 
#include <typeinfo>

#include "ProgressReporter.h"
#include "HashStreamWriter.h"

void ProgressReporter::update(const Observable& sender, const std::string& context) const {
	if (typeid(sender) == typeid(HashStreamWriter)) {
		std::cout << "\nProcessing " << context << "...\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
	else if (typeid(sender) == typeid(StrategyChecksumCalculator)) {
		std::cout << "\r" << context << " byte(s) read";
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}
