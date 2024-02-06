#pragma once

#include <string>
#include <cryptlib.h>

#include "Directory.h"
#include "StrategyChecksumCalculator.h"

class Application {
	void performScan();

	void handleLinks();
	std::unique_ptr<CryptoPP::HashTransformation> chooseAlgorithm();
	void buildDirectory();
	void displayReport();
	void startScanning();

	bool followLinks = false; 
	std::unique_ptr<Directory> dir = nullptr;
public:
	void run();
};