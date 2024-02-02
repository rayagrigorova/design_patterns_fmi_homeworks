#pragma once

#include <memory>


// I am using the Crypto++ library for the cryptographic hash functions.
// The common interface for hashing functions is HashTransformation. 
// I am going go use the strategy pattern instead of creating a derived 
// class for each of the algorithms below. 

#include <adler32.h>
#include <blake2.h>
#include <md2.h>
#include <md4.h>
#include <md5.h>
#include <sha.h>
#include <sha3.h>
#include <tiger.h>
#include <whrlpool.h>

#include "ChecksumCalculator.h"
#include "Observable.h"

class StrategyChecksumCalculator : public ChecksumCalculator, public Observable, public Observer {
	std::unique_ptr<CryptoPP::HashTransformation> strategy = nullptr;
public:
	StrategyChecksumCalculator() = default;
	StrategyChecksumCalculator(const StrategyChecksumCalculator& other);
	StrategyChecksumCalculator(std::unique_ptr<CryptoPP::HashTransformation>&& strategy);
	StrategyChecksumCalculator& operator=(const StrategyChecksumCalculator& other); 
	
	std::string calculate(std::istream& is) const override;

	void setAlgorithm(std::unique_ptr<CryptoPP::HashTransformation>&& newStrategy);

	virtual void update(const Observable& sender, const std::string& context) override;
};