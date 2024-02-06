#pragma once

#include <string>
#include <cryptlib.h>

#include "Directory.h"
#include "StrategyChecksumCalculator.h"
#include "HashStreamWriter.h"
#include "Observer.h"
#include "ProgressReporter.h"

// The application will observe HashStreamWriter 
// When HashStreamWriter detects that a key was pressed, it will inform Application 
// and application will create a snapshot of the HashStreamWriter

// Application plays the role of the caretaker class in the memento pattern
class Application : public Observer, public std::enable_shared_from_this <Application>{
	void performScan();

	void handleLinks();
	std::unique_ptr<CryptoPP::HashTransformation> chooseAlgorithm();
	void buildDirectory();
	void displayReport();
	void startScanning();

	bool followLinks = false; 
	std::unique_ptr<Directory> dir = nullptr;
	std::unique_ptr<HashStreamWriter> writer = nullptr;
	std::shared_ptr<ProgressReporter> reporter = nullptr;

	bool scanPaused = false;

	// I will use a pair instead of a stack because in this case we can only restore the last paused scan
	std::pair<HashStreamWriter::HashStreamWriterMemento, ProgressReporter::ProgressReporterMemento> toRestore;
public:
	void run();
	Application() = default; 

	virtual void update(const Observable& sender, const std::string& context) override;
};