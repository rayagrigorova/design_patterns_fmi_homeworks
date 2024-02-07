#pragma once

#include <filesystem>
#include <optional>
namespace fs = std::filesystem;

#include "AbstractFile.h"
#include "File.h"
#include "Directory.h"

class FileVisitor {
protected:
	std::optional<fs::path> rootDirPath; 
public:
	virtual ~FileVisitor() = default; 

	virtual void visitFile(const File& file) = 0;
	virtual void visitDirectory(const Directory& dir);
};