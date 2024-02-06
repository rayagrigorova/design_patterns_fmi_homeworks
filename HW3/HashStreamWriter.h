#pragma once

#include <stack>
#include <optional>

#include "FileVisitor.h"
#include "Observable.h"
#include "StrategyChecksumCalculator.h"

class HashStreamWriter : public FileVisitor, public Observable {
	StrategyChecksumCalculator calc;
	std::ostream& os;

	// A stack will be used to conduct the DFS. Otherwise it will  not be possible to restore the last point of traversal 
	std::stack<const Directory*> dirStack;
	std::optional<size_t> begin; // This index will only be set if the progress was restored from a memento 
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

		std::stack<const Directory*> dirStack;
		size_t begin;
		
		HashStreamWriterMemento(const std::stack<const Directory*>& dirStack, size_t begin);
		HashStreamWriterMemento() = default;
	};

	HashStreamWriterMemento save() const;
	void restore(const HashStreamWriterMemento& m);

	void visitDirectory(const Directory& dir)override;
};