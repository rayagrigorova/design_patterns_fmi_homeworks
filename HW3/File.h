#pragma once

#include "AbstractFile.h"

class File : public AbstractFile {
	// uintmax_t is a maximum-width unsigned integer type
	std::uintmax_t size = 0;
public:
	File(const fs::path& path);
	File() = default;

	std::uintmax_t getSize() const override;

	void accept(const FileVisitor& v) override;
};

