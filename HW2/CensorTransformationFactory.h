#pragma once

#include <unordered_map>
#include <memory>

#include "Transformations.h"

class CensorTransformationFactory {
	std::unordered_map<std::string, std::unique_ptr<CensorTransformation>> cache;

public:
	const CensorTransformation& getFlyweight(const std::string& word);
};