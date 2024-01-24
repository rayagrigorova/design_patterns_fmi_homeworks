#pragma once

#include <memory>

#include "AbstractFile.h"

class Directory : public AbstractFile{
	std::vector<std::unique_ptr<AbstractFile>> children; 
	std::uintmax_t cachedSize = 0;
public:
	Directory() = default;
	Directory(const fs::path& path);
	
	void add(std::unique_ptr<AbstractFile>&& elem);
	const std::vector<std::unique_ptr<AbstractFile>>& getChildren() const;
	std::uintmax_t getSize() const override;

	void accept(const FileVisitor& v) override;
};