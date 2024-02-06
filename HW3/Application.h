#pragma once

#include <string>
#include <cryptlib.h>

#include "Directory.h"
#include "StrategyChecksumCalculator.h"
#include "HashStreamWriter.h"
#include "ProgressReporter.h"
#include "Caretaker.h"

class Application {
	void performScan();

	void handleLinks();
	std::unique_ptr<CryptoPP::HashTransformation> chooseAlgorithm();
	void buildDirectory();
	void displayReport();
	void startScanning();

	bool followLinks = false; 
	std::unique_ptr<Directory> dir = nullptr;

	std::shared_ptr<HashStreamWriter> writer = nullptr;
	std::shared_ptr<ProgressReporter> reporter = nullptr;

	std::shared_ptr<Caretaker> caretaker = nullptr;
public:
	Application();
	void run();
};