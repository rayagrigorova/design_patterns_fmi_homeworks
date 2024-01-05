#pragma once

#include <unordered_map>
#include <memory>

#include "Transformations.h"

const size_t MAX_WORD_LEN = 4;

class CensorTransformationFactory {
	std::unordered_map<std::string, std::unique_ptr<CensorTransformation>> cache;

public:
	const CensorTransformation& getFlyweight(const std::string& word) {
		// The word is 4 characters or less
		if (word.size() <= MAX_WORD_LEN) {
			// If the word isn't in the cache yet 
			if (cache.count(word) == 0) {
				cache[word] = std::make_unique<CensorTransformation>(word);
			}
			return *cache[word];
		}
		// For words longer than 4 characters, return a newly created object
		static CensorTransformation temp = CensorTransformation(word);
		return temp;
	}
};