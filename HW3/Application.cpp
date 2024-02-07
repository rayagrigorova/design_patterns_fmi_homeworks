#include <iostream>
#include <memory>
#include <vector>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <functional> // for std::function, std::function is a function wrapper 

#include "Application.h"

#include "ReportWriter.h"
#include "HashStreamWriter.h"
#include "ProgressReporter.h"
#include "FollowBuilder.h"
#include "NoFollowBuilder.h"
#include "File.h"

namespace fs = std::filesystem;

std::unordered_map<std::string, std::function<std::unique_ptr<CryptoPP::HashTransformation>()>> hashingFunctions = {
	{"Adler32", []() { return std::make_unique<CryptoPP::Adler32>(); }},
	{"BLAKE2b", []() { return std::make_unique<CryptoPP::BLAKE2b>(); }},
	{"MD2", []() { return std::make_unique<CryptoPP::MD2>(); }},
	{"MD4", []() { return std::make_unique<CryptoPP::MD4>(); }},
	{"MD5", []() { return std::make_unique<CryptoPP::MD5>(); }},
	{"SHA1", []() { return std::make_unique<CryptoPP::SHA1>(); }},
	{"SHA256", []() { return std::make_unique<CryptoPP::SHA256>(); }},
	{"SHA512", []() { return std::make_unique<CryptoPP::SHA512>(); }},
	{"Tiger", []() { return std::make_unique<CryptoPP::Tiger>(); }},
	{"Whirlpool", []() { return std::make_unique<CryptoPP::Whirlpool>(); }},
};

void Application::run() {
	while (1) {
		std::cout << "Enter 's' to start a scan and 'x' to exit" << std::endl;
		std::cout << "To pause the scan, press any key. The program checks for a request to pause scanning after each processed file." << std::endl;
		char input;
		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		switch (input) {
		case 'x': 
			return;
		case 's':
			performScan();
			break;
		default:
			std::cout << "Invalid command" << std::endl;
			break;
		}
	}
}

void Application::handleLinks() {
	std::cout << "Please, choose how you want to handle symbolic links/shortcuts:" << std::endl;
	std::cout << "Option 1: Calculating the checksum of the actual symbolic link or shortcut" << std::endl;
	std::cout << "Option 2: Traversing the target of the symbolic link or shortcut" << std::endl;
	std::cout << "Enter '1' for Option 1 and '2' for Option 2" << std::endl;

	while (1) {
		char ans;
		std::cin >> ans;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (ans == '1') {
			followLinks = false;
			break;
		}
		else if(ans == '2') {
			followLinks = true;;
			break;
		}
		else {
			std::cout << "The option you have entered is invalid." << std::endl;
		}
	}
}

void Application::performScan() {
	handleLinks();
	buildDirectory();
	displayReport();
	startScanning();
}

std::unique_ptr<CryptoPP::HashTransformation> Application::chooseAlgorithm() {
	std::cout << "Please, choose a hashing algorithm. Available options:" << std::endl;

	for (auto& pair : hashingFunctions) {
		std::cout << pair.first << ' ';
	}
	std::cout << std::endl;

	while (1) {
		std::string name;
		std::cin >> name;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (hashingFunctions.count(name) != 0) {
			std::unique_ptr<CryptoPP::HashTransformation> result = hashingFunctions[name]();
			return std::move(result);
		}
		else {
			std::cout << "The algorithm name you have chosen is invalid. Please, enter again." << std::endl;
		}
	}
	return nullptr;
}

void Application::displayReport() {
	std::cout << "Do you want a report of all files and their sizes to be scanned before the actual scan is started (y/n)?" << std::endl;

	while (1) {
		char input;
		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input == 'y') {
			ReportWriter rw(std::cout);
			rw.visitDirectory(*dir);
			break;
		}
		else if (input == 'n') {
			return;
		}
		else{
			std::cout << "Invalid command" << std::endl;
		}
	}
	std::cout << "Press Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Application::buildDirectory() {
	std::unique_ptr<AbstractBuilder> builder;
	if (followLinks) {
		builder = std::move(std::make_unique<FollowBuilder>());
	}
	else {
		builder = std::move(std::make_unique<NoFollowBuilder>());
	}

	std::unique_ptr<Directory> builtResult;
	while (1) {
		std::cout << "Please, enter the path of the target directory:" << std::endl;
		std::string input;
		std::getline(std::cin, input);

		fs::path filePath(input);
		// The fs::exists() and fs::is_directory() functions could throw an error 
		try {
			if (!fs::exists(filePath) || !fs::is_directory(filePath)) {
				std::cout << "The path you have entered is invalid. Please, enter again." << std::endl;
			}
			else {
				dir = std::move(builder->buildDir(filePath));
				return;
			}
		}
		catch (const fs::filesystem_error& e) {
			std::cout << "An error occurred when reading the file path: " << e.what() << std::endl;
		}
	}
}

void Application::startScanning() {
	std::cout << "Please, enter the name of the file where the hashes will be saved: " << std::endl;
	std::string fileName;
	std::getline(std::cin, fileName);

	if (std::filesystem::exists(fileName)) {
		std::cout << "File already exists. Do you wish to overwrite it? (y/n):" << std::endl;
		char ans;
		while (1) {
			std::cin >> ans;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (ans == 'y' || ans == 'n') {
				break;
			}
			else {
				std::cout << "Invalid command" << std::endl;
			}
		}
		if (ans == 'n') {
			std::cout << "Scan cancelled." << std::endl;
			return;
		}
	}
	
	std::ofstream file(fileName);
	if (!file) {
		std::cerr << "Failed to open file for writing." << std::endl;
		return;
	}
	std::unique_ptr<CryptoPP::HashTransformation> alg = std::move(chooseAlgorithm());
	writer = std::make_shared<HashStreamWriter>(file, StrategyChecksumCalculator(std::move(alg)));
	reporter = std::make_shared<ProgressReporter>(dir->getSize()); 

	caretaker = std::make_shared<Caretaker>(writer, reporter);

	writer->subscribe(reporter);
	writer->subscribe(caretaker);

	writer->visitDirectory(*dir);

	while (caretaker->paused()) {
		waitForResume();
		writer->visitDirectory(*dir);
	}

	if (file.fail()) {
		std::cerr << "An error occurred when writing to the file" << std::endl;
		return;
	}
	std::cout << std::endl << "The scan was successful" << std::endl;
}

void Application::waitForResume() {
	std::cout << std::endl << "Scan paused. Press Enter to resume." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	caretaker->restore();
}
