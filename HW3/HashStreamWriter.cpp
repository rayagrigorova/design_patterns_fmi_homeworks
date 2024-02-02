#include <fstream>

#include "HashStreamWriter.h"
#include "ProgressReporter.h"

HashStreamWriter::HashStreamWriter(std::ostream& os, std::unique_ptr<CryptoPP::HashTransformation>&& strategy)
	: os(os), calc(std::move(strategy)){}

HashStreamWriter::HashStreamWriter(std::ostream& os, StrategyChecksumCalculator&& calc) : os(os), calc(std::move(calc)){
}

void HashStreamWriter::visitFile(const File& file) {
	// Open the file since the calculator works with an open stream
	std::ifstream ifs(file.getPath(), std::ios::binary);
	if (!ifs.is_open()) {
		std::cerr << "The file could not be opened" << std::endl;
		return;
	}
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

void HashStreamWriter::visitDirectory(const Directory& dir) {
	if (!rootDirPath.has_value()) {
		rootDirPath = dir.getPath();
		directoryTraversed = &dir;
	}
	const std::vector<std::unique_ptr<AbstractFile>>& children = dir.getChildren();
	for (size_t i = 0; i < children.size(); i++) {
		currentIndex = i;
		children[i]->accept(*this);
	}

	if (dir.getPath() == rootDirPath.value_or(fs::path())) {
		rootDirPath.reset();
		directoryTraversed = nullptr;
	}
}

void HashStreamWriter::Memento::setStreamWriterState(const Directory* directoryTraversed, const std::optional<fs::path>& rootDirPath,
	const StrategyChecksumCalculator& calc, const std::vector<std::shared_ptr<Observer>>& subscribers, size_t currentIndex) {
	
	this->directoryTraversed = directoryTraversed;
	this->rootDirPath = rootDirPath;
	this->calc = calc;
	this->subscribers = subscribers;
	this->currentIndex = currentIndex;
}

void HashStreamWriter::Memento::setProgressReporterState(std::uintmax_t totalBytes, std::uintmax_t bytesProcessed,
	const std::chrono::time_point<std::chrono::steady_clock>& startTime) {

	this->totalBytes = totalBytes;
	this->bytesProcessed = bytesProcessed;
	this->startTime = startTime;
}

HashStreamWriter::Memento::Memento(const Directory* directoryTraversed, const std::optional<fs::path>& rootDirPath,
	const StrategyChecksumCalculator& calc, const std::vector<std::shared_ptr<Observer>>& subscribers, size_t currentIndex,
	std::uintmax_t totalBytes, std::uintmax_t bytesProcessed, const std::chrono::time_point<std::chrono::steady_clock>& startTime) {
	setStreamWriterState(directoryTraversed, rootDirPath, calc, subscribers, currentIndex);
	setProgressReporterState(totalBytes, bytesProcessed, startTime); 
}

HashStreamWriter::Memento::Memento(const HashStreamWriter& hsr) {
	setStreamWriterState(hsr.directoryTraversed, hsr.rootDirPath, hsr.calc, hsr.subscribers, hsr.currentIndex);
}

HashStreamWriter::Memento::Memento(const ProgressReporter& r) {
	setProgressReporterState(r.totalBytes, r.bytesProcessed, r.startTime);
}

HashStreamWriter::Memento HashStreamWriter::save() const {
	return HashStreamWriter::Memento(*this);
}

void HashStreamWriter::restore(const Memento& m) {
	directoryTraversed = m.directoryTraversed;
	rootDirPath = m.rootDirPath;
	calc = m.calc;
	subscribers = m.subscribers;
	currentIndex = m.currentIndex; 
}



