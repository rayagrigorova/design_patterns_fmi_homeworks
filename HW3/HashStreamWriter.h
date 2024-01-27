#pragma once

#include "FileVisitor.h"
#include "Observable.h"
#include "StrategyChecksumCalculator.h"

class HashStreamWriter : public FileVisitor, public Observable {
	StrategyChecksumCalculator calc;
	std::ostream& os; 
public:
	HashStreamWriter(std::ostream& os, std::unique_ptr<CryptoPP::HashTransformation>&& strategy);

	void visitFile(const File& file) const override;

	virtual void subscribe(std::shared_ptr<Observer> o) override;
};