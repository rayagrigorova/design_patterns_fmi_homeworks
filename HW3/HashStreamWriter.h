#pragma once

#include "FileVisitor.h"
#include "StrategyChecksumCalculator.h"

class HashStreamWriter : public FileVisitor {
	StrategyChecksumCalculator calc;
	std::ostream& os; 
public:
	HashStreamWriter(std::ostream& os, std::unique_ptr<CryptoPP::HashTransformation>&& strategy);

	void visitFile(const File& file) const override;
};