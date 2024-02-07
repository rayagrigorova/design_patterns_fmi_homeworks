#pragma once

#include <unordered_set>

#include "AbstractFile.h"
#include "File.h"
#include "Directory.h"

// The 'builder' classes in my case more closely resemble 
// the 'template method' pattern rather than the 'builder' pattern (combined with factory). 

// The builder classes create the file structure to be traversed. The resulting structure should be a tree. 
class AbstractBuilder {
protected:
	// Add paths to visited files and directories here 
	// This is done in order to prevent creating cycles 
	std::unordered_set<fs::path> visited;

	virtual std::unique_ptr<AbstractFile>buildLink(const fs::path& path) = 0;

public:
	virtual ~AbstractBuilder() = default;

	virtual std::unique_ptr<File>buildFile(const fs::path& path);
	virtual std::unique_ptr<Directory>buildDir(const fs::path& path);
};