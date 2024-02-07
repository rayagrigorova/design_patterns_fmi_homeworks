#include <fstream>
#include <conio.h>
#include <unordered_set>

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

HashStreamWriter::HashStreamWriterMemento::HashStreamWriterMemento(const std::deque<const Directory*>& dirStack, size_t currentInd)
	: dirStack(dirStack), currentInd(currentInd) {

}

HashStreamWriter::HashStreamWriterMemento HashStreamWriter::save() const {
	return HashStreamWriter::HashStreamWriterMemento(dirStack, currentInd);
}

void HashStreamWriter::restore(const HashStreamWriter::HashStreamWriterMemento& m) {
	dirStack = m.dirStack;
	currentInd = m.currentInd;
}

void HashStreamWriter::visitDirectory(const Directory& rootDir) {
	// If there was no pausing happening
	if (dirStack.empty()) {
		rootDirPath = rootDir.getPath();
		dirStack.push_front(&rootDir);
		currentInd = 0;
	}

	while (!dirStack.empty()) {
		const Directory* currentDir = dirStack.front();

		const std::vector<std::unique_ptr<AbstractFile>>& children = currentDir->getChildren();
		for (size_t i = currentInd; i < children.size(); i++) {
			currentInd = i;

			if (typeid(*children[i]) == typeid(File)) {
				children[i]->accept(*this);
			}
			else {
				const Directory* childDir = dynamic_cast<Directory*>(children[i].get());
				dirStack.push_back(childDir);
			}

			// A key was pressed and this should be handled 
			if (_kbhit()) {
				int ch = _getch();
				std::cin.clear();

				currentInd++;
				if (currentInd >= children.size()) { // If it's time to progress to the next directory in the stack 
					dirStack.pop_front();
					currentInd = 0;

					// Corner case: the key was pressed after all directories and files were processed 
					// In this case, don't save a memento. 
					if (!dirStack.size()) {
						return;
					}
				}
				// Notify caretaker to save the states of HashStreamWriter and ProgressReporter
				notifySubscribers("<Save>");
				return;
			}
		}
		dirStack.pop_front();
		currentInd = 0;
	}

	rootDirPath.reset();
}




