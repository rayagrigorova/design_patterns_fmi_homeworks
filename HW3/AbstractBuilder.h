#pragma once

#include <unordered_set>

#include "AbstractFile.h"
#include "File.h"
#include "Directory.h"

// The 'builder' classes in my case more closely resemble 
// the 'template method' pattern rather than the 'builder' pattern. 
class AbstractBuilder {
protected:
	// Add paths to visited files and directories here 
	// This is done in order to prevent creating cycles 
	std::unordered_set<fs::path> visited;

	virtual std::unique_ptr<AbstractFile>buildFile(const fs::path& path);
	virtual std::unique_ptr<AbstractFile>buildDir(const fs::path& path);
	virtual std::unique_ptr<AbstractFile>buildLink(const fs::path& path)= 0;

	std::unique_ptr<AbstractFile> result = nullptr;
public:
	virtual std::unique_ptr<AbstractFile> build(const fs::path& path); 
	std::unique_ptr<AbstractFile>&& getResult();
};