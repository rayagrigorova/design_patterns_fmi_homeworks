#pragma once

#include "ProgressReporter.h"
#include "HashStreamWriter.h"
#include "Observer.h"

// This class will be subscribed to HashStreamWriter by the Application 
// This way it will know when to save the states of HashStreamWriter and ProgressReporter
class Caretaker : public Observer{
	// This could be a pair in the context of the app (because only one scan can be paused at a time) but I chose a stack since it's more general.
	// The stack isn't from pairs because the mementos for HashStreamWriterMemento and ProgressReporterMemento are saved at different times. 
	std::stack<HashStreamWriter::HashStreamWriterMemento> writerHistory;
	std::stack<ProgressReporter::ProgressReporterMemento> reporterHistory;

	std::shared_ptr<HashStreamWriter> originalWriter = nullptr;
	std::shared_ptr<ProgressReporter> originalReporter = nullptr; 
public:
	Caretaker() = default;
	Caretaker(std::shared_ptr<HashStreamWriter> originalWriter, std::shared_ptr<ProgressReporter> originalReporter);

	virtual void update(const Observable& sender, const std::string& context) override;

	// This function returns true if the stack is non empty (indicating that there are paused scans waiting to be restored)
	bool paused() const;
	void restore(); 
};