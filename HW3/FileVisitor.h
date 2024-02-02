#pragma once

#include <filesystem>
namespace fs = std::filesystem;

#include "AbstractFile.h"
#include "File.h"
#include "Directory.h"

class FileVisitor {
protected:
	std::optional<fs::path> rootDirPath; 
public:
	virtual ~FileVisitor() = default; 

	// The concrete visitors will implement the visitFile() function
	// The methods are not constant, because the path of the root directory(where the scan begins) should be saved. 
	virtual void visitFile(const File& file) = 0;
	virtual void visitDirectory(const Directory& dir);
};