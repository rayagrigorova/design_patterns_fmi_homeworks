#include "CensorTransformationFactory.h"

CensorTransformation& CensorTransformationFactory::getFlyweight(const std::string& word) {
	// if the word is longer than 4 symbols or it isn't in the cache yet, add it to the cache 
	if (word.size() > MAX_WORD_LEN || cache.count(word) == 0) {
		cache[word] = std::make_unique<CensorTransformation>(word);
	}
	return *cache[word];
}