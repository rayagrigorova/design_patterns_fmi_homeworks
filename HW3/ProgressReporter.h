#pragma once

#include "Observer.h"
#include <string>
#include <chrono>

class Memento;

class ProgressReporter : public Observer{
	friend class Memento;

	std::uintmax_t totalBytes = 0; 
	std::uintmax_t bytesProcessed = 0;
	
	std::chrono::time_point<std::chrono::steady_clock> startTime;
public:
	ProgressReporter() = default;
	ProgressReporter(std::uintmax_t totalBytes);
	virtual void update(const Observable& sender, const std::string& context) override;

	HashStreamWriter::Memento save() const;
	void restore(const HashStreamWriter::Memento& m);
};
