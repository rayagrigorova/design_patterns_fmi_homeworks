#pragma once

#include <filesystem>

#include "FileVisitor.h"

// this creates an alias for the namespace 
namespace fs = std::filesystem;

class AbstractFile {
protected:
	fs::path path;
public:
	virtual ~AbstractFile() = default;
	AbstractFile() = default;
	AbstractFile(const fs::path& path);

	virtual std::uintmax_t getSize() const = 0;
	const fs::path& getPath() const;

	virtual void accept(const FileVisitor& v) = 0;
};