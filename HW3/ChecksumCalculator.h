#pragma once

#include <iostream>
#include <string>

class ChecksumCalculator {
public:
	virtual ~ChecksumCalculator() = default;
	virtual std::string calculate(std::istream& is) const = 0;
};