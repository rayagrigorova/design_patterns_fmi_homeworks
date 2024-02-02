#pragma once

#include "Observer.h"
#include <string>
#include <chrono>

class ProgressReporter : public Observer{
	std::uintmax_t totalBytes = 0; 
	std::uintmax_t bytesProcessed = 0;
	
	// This field is a time point measured by std::chrono::steady_clock 
	// (this clock only moves forward and isn't affected by changes in system time)
	std::chrono::time_point<std::chrono::steady_clock> startTime;
public:
	ProgressReporter() = default;
	ProgressReporter(std::uintmax_t totalBytes);
	virtual void update(const Observable& sender, const std::string& context) override;
};
