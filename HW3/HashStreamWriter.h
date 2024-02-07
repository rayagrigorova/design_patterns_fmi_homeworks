#pragma once

#include <stack>
#include <deque>
#include <optional>

#include "FileVisitor.h"
#include "Observable.h"
#include "StrategyChecksumCalculator.h"

class HashStreamWriter : public FileVisitor, public Observable {
	StrategyChecksumCalculator calc;
	std::ostream& os;
	
	// The directory traversal will be conducted using a deque
	std::deque<const Directory*> dirStack;
	// This variable will be used to resume the scanning if it was stopped 
	size_t currentInd = 0;
public:
	HashStreamWriter(std::ostream& os, std::unique_ptr<CryptoPP::HashTransformation>&& strategy);
	HashStreamWriter(std::ostream& os, StrategyChecksumCalculator&& calc);

	void visitFile(const File& file) override;
	void visitDirectory(const Directory& rootDir) override;

	virtual void subscribe(std::shared_ptr<Observer> o) override;

	// I chose not to copy StrategyChecksumCalculator calc, because it stays the same for the lifetime of the object.
	// The stream also stays the same (moreover copying streams is not possible)
	class HashStreamWriterMemento {
		// Allow HashStreamWriter to access the private fields of the memento 
		friend class HashStreamWriter;

		std::deque<const Directory*> dirStack;
		size_t currentInd;
		HashStreamWriterMemento(const std::deque<const Directory*>& dirStack, size_t currentInd);
		HashStreamWriterMemento() = default;
	};

	HashStreamWriterMemento save() const;
	void restore(const HashStreamWriterMemento& m);
};