#pragma once

#include <string>

class Application {
	void performScan();
	void  handleLinks();
	void chooseAlgorithm();
	void startScanning();

	bool followLinks = false; 
	std::string hashingAlgorithm;
public:
	void run();
};