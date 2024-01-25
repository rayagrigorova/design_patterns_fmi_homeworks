#pragma once

#include "AbstractFile.h"
#include "File.h"
#include "Directory.h"

class FileVisitor {
public:
	virtual ~FileVisitor() = default; 

	// The concrete visitors will implement the visitFile() function
	virtual void visitFile(const File& file) const = 0;
	virtual void visitDirectory(const Directory& dir) const;
};