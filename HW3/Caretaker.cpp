#include "Caretaker.h"

Caretaker::Caretaker(std::shared_ptr<HashStreamWriter> originalWriter, std::shared_ptr<ProgressReporter> originalReporter) 
		: originalWriter(originalWriter), originalReporter(originalReporter){

}

void Caretaker::update(const Observable& sender, const std::string& context) {
	if (context == "<Save>") {
		if (typeid(sender) == typeid(HashStreamWriter)) {
			history.push({ originalWriter->save(), originalReporter->save() });
		}
		else {
			std::cerr << "Unknown sender" << std::endl;
		}
	}
}

bool Caretaker::paused() const {
	return !history.empty();
}

void Caretaker::restore() {
	if (history.empty()) {
		std::cerr << "No state to restore" << std::endl;
	}
	originalWriter->restore(history.top().first);
	originalReporter->restore(history.top().second);

	history.pop();
}