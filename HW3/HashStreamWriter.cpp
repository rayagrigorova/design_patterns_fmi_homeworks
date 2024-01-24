#include "HashStreamWriter.h"

#include <fstream>

HashStreamWriter::HashStreamWriter(std::ostream& os, std::unique_ptr<CryptoPP::HashTransformation>&& strategy)
	: os(os), calc(std::move(strategy)){}

void HashStreamWriter::visitFile(File& file) const {
	std::ifstream ifs(file.getPath(), std::ios::binary);
	if (!ifs.is_open()) {
		std::cerr << "The file could not be opened\n";
		return;
	}
	std::string resultHash = calc.calculate(ifs);
	os << file.getPath().string() << " " << resultHash << "\n";
	ifs.close();
}