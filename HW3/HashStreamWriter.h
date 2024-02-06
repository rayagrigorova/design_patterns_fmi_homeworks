#pragma once

#include "FileVisitor.h"
#include "Observable.h"
#include "StrategyChecksumCalculator.h"

class HashStreamWriter : public FileVisitor, public Observable {
	StrategyChecksumCalculator calc;
	std::ostream& os;
	// This non-owning pointer will be used to keep track of the current file hashStreamWriter is working with 
	const AbstractFile* lastCallArgument = nullptr; 
public:
	HashStreamWriter(std::ostream& os, std::unique_ptr<CryptoPP::HashTransformation>&& strategy);
	HashStreamWriter(std::ostream& os, StrategyChecksumCalculator&& calc);

	void visitFile(const File& file) override;

	virtual void subscribe(std::shared_ptr<Observer> o) override;

	// The state of HashStreamWriter only includes the last file that was (about to) be traversed
	// I chose not to copy StrategyChecksumCalculator calc, because it stays the same for the lifetime of the object.
	// The stream also stays the same (moreover copying streams is not possible)
	class HashStreamWriterMemento {
		// Allow HashStreamWriter to access the private fields of the memento 
		friend class HashStreamWriter;

		const AbstractFile* lastCallArgument = nullptr;
		HashStreamWriterMemento(const AbstractFile* lastCallArgument);
	};

	HashStreamWriterMemento save() const;
	void restore(const HashStreamWriterMemento& m);
};