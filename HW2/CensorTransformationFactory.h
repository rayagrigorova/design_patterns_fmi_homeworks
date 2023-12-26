#pragma once

#include <unordered_map>
#include <memory>

#include "Transformations.h"

const size_t MAX_WORD_LEN = 4;

class CensorTransformationFactory {
	std::unordered_map<std::string, std::unique_ptr<CensorTransformation>> cache;

public:
	CensorTransformation& getFlyweight(const std::string& word);
};