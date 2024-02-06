#include <fstream>

#include "HashStreamWriter.h"
#include "ProgressReporter.h"

HashStreamWriter::HashStreamWriter(std::ostream& os, std::unique_ptr<CryptoPP::HashTransformation>&& strategy)
	: os(os), calc(std::move(strategy)){}

HashStreamWriter::HashStreamWriter(std::ostream& os, StrategyChecksumCalculator&& calc) : os(os), calc(std::move(calc)){
}

void HashStreamWriter::visitFile(const File& file) {
	lastCallArgument = &file;

	// Open the file since the calculator works with an open stream
	std::ifstream ifs(file.getPath(), std::ios::binary);
	if (!ifs.is_open()) {
		std::cerr << "The file could not be opened" << std::endl;
		return;
	}
	// Notify subscribers that the respective file was opened 
	notifySubscribers(file.getPath().filename().string());

	std::string resultHash = calc.calculate(ifs);
	os << resultHash << " " << fs::relative(file.getPath(), rootDirPath.value()) << std::endl;
	ifs.close();
}

// When ProgressReporter subscribes to HashStreamWriter, HashStreamWriter also subscribes it to the checksum calculator.
// In this way ProgressReporter will directly receive all status updates from the calculator directly.
void HashStreamWriter::subscribe(std::shared_ptr<Observer> o) {
	Observable::subscribe(o);
	calc.subscribe(o);
}

HashStreamWriter::HashStreamWriterMemento::HashStreamWriterMemento(const AbstractFile* lastCallArgument) {
	this->lastCallArgument = lastCallArgument;
}

HashStreamWriter::HashStreamWriterMemento HashStreamWriter::save() const {
	return HashStreamWriter::HashStreamWriterMemento(lastCallArgument);
}

void HashStreamWriter::restore(const HashStreamWriter::HashStreamWriterMemento& m) {
	lastCallArgument = m.lastCallArgument;
}


