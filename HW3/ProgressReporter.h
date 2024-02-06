#pragma once

#include <string>
#include <chrono>

#include "Observer.h"
#include "Observable.h"

// Caretaker is an observable because it reports to the caretaker when its state should be captured 
class ProgressReporter : public Observer, public Observable{
	std::uintmax_t totalBytes = 0; 
	std::uintmax_t bytesProcessed = 0;
	
	// This field is a time point measured by std::chrono::steady_clock 
	// (this clock only moves forward and isn't affected by changes in system time)
	std::chrono::time_point<std::chrono::steady_clock> startTime;
public:
	ProgressReporter() = default;
	ProgressReporter(std::uintmax_t totalBytes);
	virtual void update(const Observable& sender, const std::string& context) override;

	class ProgressReporterMemento {
		friend class ProgressReporter;

		std::uintmax_t totalBytes = 0;
		std::uintmax_t bytesProcessed = 0;
		std::chrono::time_point<std::chrono::steady_clock> startTime;

		ProgressReporterMemento(std::uintmax_t totalBytes, std::uintmax_t bytesProcessed,
			const std::chrono::time_point<std::chrono::steady_clock>& startTime);
	};

	ProgressReporterMemento save() const;
	void restore(const ProgressReporterMemento& m);
};
