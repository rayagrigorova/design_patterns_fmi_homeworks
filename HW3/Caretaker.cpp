#include "Caretaker.h"

Caretaker::Caretaker(std::shared_ptr<HashStreamWriter> originalWriter, std::shared_ptr<ProgressReporter> originalReporter) 
		: originalWriter(originalWriter), originalReporter(originalReporter){

}

void Caretaker::update(const Observable& sender, const std::string& context) {
	if (context == "<Save>") {
		if (typeid(sender) == typeid(HashStreamWriter)) {
			writerHistory.push(originalWriter->save());
			//try {
			//	const HashStreamWriter& writer = dynamic_cast<const HashStreamWriter&>(sender);
			//	writerHistory.push(writer.save());
			//}
			//catch (const std::bad_cast& e) {
			//	std::cerr << "Dynamic cast failed: " << e.what() << std::endl;
			//}
		}
		else if (typeid(sender) == typeid(ProgressReporter)) {
			reporterHistory.push(originalReporter->save());
			//try {
			//	const ProgressReporter& reporter = dynamic_cast<const ProgressReporter&>(sender);
			//	reporterHistory.push(reporter.save());
			//}
			//catch (const std::bad_cast& e) {
			//	std::cerr << "Dynamic cast failed: " << e.what() << std::endl;
			//}
		}
		else {
			std::cerr << "Unknown sender" << std::endl;
		}
	}
}

bool Caretaker::paused() const {
	return !writerHistory.empty();
}

void Caretaker::restore() {
	// Check if the sizes are different or are the same but equal to 0
	if (writerHistory.size() != reporterHistory.size() || !writerHistory.size()) {
		std::cerr << "The two caretaker stack are not in sync or are empty" << std::endl; 
		return;
	}
	originalWriter->restore(writerHistory.top());
	originalReporter->restore(reporterHistory.top());

	writerHistory.pop();
	reporterHistory.pop();
}