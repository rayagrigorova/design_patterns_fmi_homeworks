#include <fstream>

#include "HashStreamWriter.h"
#include "ProgressReporter.h"

HashStreamWriter::HashStreamWriter(std::ostream& os, std::unique_ptr<CryptoPP::HashTransformation>&& strategy)
	: os(os), calc(std::move(strategy)){}

void HashStreamWriter::visitFile(const File& file) const {
	// Open the file since the calculator works with an open stream
	std::ifstream ifs(file.getPath(), std::ios::binary);
	if (!ifs.is_open()) {
		std::cerr << "The file could not be opened\n";
		return;
	}
	notifySubscribers(file.getPath().filename().string());

	std::string resultHash = calc.calculate(ifs);
	os << "File path: " << file.getPath().string() << " Hash: " << resultHash << "\n";
	ifs.close();
}

void HashStreamWriter::subscribe(std::shared_ptr<Observer> o) {
	Observable::subscribe(o);
	calc.subscribe(o);
}
