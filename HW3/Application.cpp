#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <filesystem>

#include "Application.h"

#include "StrategyChecksumCalculator.h"
#include "ReportWriter.h"
#include "HashStreamWriter.h"
#include "ProgressReporter.h"
#include "FollowBuilder.h"
#include "NoFollowBuilder.h"

namespace fs = std::filesystem;

static std::vector<std::string> hashingFunctions = { "Adler32", "BLAKE2b", "MD2", "MD4", "MD5", "SHA1", "SHA256", "SHA512", "Tiger", "Whirlpool"};

void Application::run() {
	while (1) {
		std::cout << "Enter 's' to start a scan and 'x' to exit\n";
		char input;
		std::cin >> input;
		
		switch (input) {
		case 'x': 
			return;
		case 's':
			performScan();
			break;
		default:
			std::cout << "Invalid command\n";
			break;
		}
	}
}

void Application::handleLinks() {
	std::cout << "Please, choose how you want to handle symbolic links/shortcuts:\n";
	std::cout << "Option 1: Calculating the checksum of the actual symbolic link or shorctut\n";
	std::cout << "Option 2: Traversing the target of the symbolic link or shortcut\n";
	std::cout << "Enter '1' for Option 1 and '2' for Option 2\n";

	bool flag = 1;
	while (flag) {
		char ans;
		std::cin >> ans;
		switch (ans) {
		case '1':
			followLinks = false;
			flag = false;
			break;
		case '2':
			followLinks = true;
			flag = false;
			break;
		default:
			std::cout << "The option you have entered is invalid.\n";
		}
	}
}

void Application::performScan() {
	handleLinks();
	chooseAlgorithm();
}

void Application::chooseAlgorithm() {
	std::cout << "Please, choose a hashing algorithm:\n";
	for (int i = 0; i < hashingFunctions.size(); i++) {
		std::cout << hashingFunctions[i] << " ";
	}
	while (1) {
		std::string name;
		std::cin >> name;
		if (std::find(hashingFunctions.begin(), hashingFunctions.end(), name) != hashingFunctions.end()) {
			hashingAlgorithm = name;
			return;
		}
		else {
			std::cout << "The algorithm name you have chosen is invalid. Please, enter again.\n";
		}
	}
}

void Application::startScanning() {
	StrategyChecksumCalculator calc; 

	if (hashingAlgorithm == "Adler32") {
		calc.setAlgorithm(std::make_unique<CryptoPP::Adler32>());
	} 
	else if (hashingAlgorithm == "BLAKE2b") {
		calc.setAlgorithm(std::make_unique<CryptoPP::BLAKE2b>());
	}
	else if (hashingAlgorithm == "MD2") {
		calc.setAlgorithm(std::make_unique<CryptoPP::MD2>());
	}
	else if (hashingAlgorithm == "MD4") {
		calc.setAlgorithm(std::make_unique<CryptoPP::MD2>());
	}
	else if (hashingAlgorithm == "MD5") {
		calc.setAlgorithm(std::make_unique<CryptoPP::MD2>());
	}
	else if (hashingAlgorithm == "SHA1") {
		calc.setAlgorithm(std::make_unique<CryptoPP::SHA1>());
	}
	else if (hashingAlgorithm == "SHA256") {
		calc.setAlgorithm(std::make_unique<CryptoPP::SHA256>());
	}
	else if (hashingAlgorithm == "SHA512") {
		calc.setAlgorithm(std::make_unique<CryptoPP::SHA512>());
	}
	else if (hashingAlgorithm == "Tiger") {
		calc.setAlgorithm(std::make_unique<CryptoPP::Tiger>());
	}
	else if (hashingAlgorithm == "Whirlpool") {
		calc.setAlgorithm(std::make_unique<CryptoPP::Whirlpool>());
	}
	else {
		std::cout << "An error has occurred. The hasing algorithm is unknown\n";
		return;
	}

	std::unique_ptr<AbstractBuilder> builder;
	if (followLinks) {
		builder = std::move(std::make_unique<FollowBuilder>());
	}
	else {
		builder = std::move(std::make_unique<NoFollowBuilder>());
	}

	std::unique_ptr<Directory> builtResult; 
	while (1) {
		std::cout << "Please, enter the path of the target directory:\n";
		std::string input;
		std::cin >> input; 

		fs::path filePath(input);
		if (!fs::exists(filePath) || fs::is_directory(filePath)) {
			std::cout << "The path you have entered is invalid. Please, enter again.\n";
		}
		else {
			builtResult = std::move(builder->buildDir(filePath));
			break;
		}
	}

	HashStreamWriter writer(std::move(calc));
	writer.subscribe(std::make_unique<ProgressReporter>(builtResult->getSize()));
	writer.visitDirectory(*builtResult);
}
