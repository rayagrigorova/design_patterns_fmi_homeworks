#pragma once

#include "CensorTransformationFactory.h"

const size_t MAX_WORD_LEN = 4;

const CensorTransformation& CensorTransformationFactory::getFlyweight(const std::string& word) {
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
