#include <fstream>
#include <cstdio>

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

HashStreamWriter::HashStreamWriterMemento::HashStreamWriterMemento(const std::stack<const Directory*>& dirStack, size_t begin) 
	: dirStack(dirStack), begin(begin){

}

HashStreamWriter::HashStreamWriterMemento HashStreamWriter::save() const {
	return HashStreamWriter::HashStreamWriterMemento(dirStack, begin.value());
}

void HashStreamWriter::restore(const HashStreamWriter::HashStreamWriterMemento& m) {
	dirStack = m.dirStack;
	begin.value() = m.begin;
}

void HashStreamWriter::visitDirectory(const Directory& rootDir) {
    while (!dirStack.empty()) dirStack.pop();

    rootDirPath = rootDir.getPath();
    dirStack.push(const_cast<Directory*>(&rootDir)); 

    while (!dirStack.empty()) {
        const Directory* currentDir = dirStack.top();
        dirStack.pop();

        const std::vector<std::unique_ptr<AbstractFile>>& children = currentDir->getChildren();
		size_t start = (begin.has_value()) ? begin.value() : 0;
		for (size_t i = start; i < children.size(); i++){
			if (getchar()) {
				notifySubscribers("");
			}
			if (typeid(*children[i]) == typeid(File)) {
				children[i]->accept(*this);
			}
			else {
				const Directory* childDir = dynamic_cast<Directory*>(children[i].get());
				dirStack.push(childDir);
			}
        }
    }

    rootDirPath.reset();
}


