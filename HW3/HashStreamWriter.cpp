#include <fstream>

#include "HashStreamWriter.h"
#include "ProgressReporter.h"

HashStreamWriter::HashStreamWriter(std::unique_ptr<CryptoPP::HashTransformation>&& strategy)
	: calc(std::move(strategy)){}

HashStreamWriter::HashStreamWriter(StrategyChecksumCalculator&& calc) : calc(std::move(calc)){

}


void HashStreamWriter::visitFile(const File& file) const {
	// Open the file since the calculator works with an open stream
	std::ifstream ifs(file.getPath(), std::ios::binary);
	if (!ifs.is_open()) {
		std::cerr << "The file could not be opened\n";
		return;
	}
	notifySubscribers(file.getPath().filename().string());

	std::string resultHash = calc.calculate(ifs);
	std::cout << resultHash << " " << file.getPath().string() << "\n";
	ifs.close();
}

void HashStreamWriter::subscribe(std::shared_ptr<Observer> o) {
	Observable::subscribe(o);
	calc.subscribe(o);
}


