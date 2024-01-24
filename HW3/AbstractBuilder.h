#pragma once

#include <unordered_set>

#include "File.h"
#include "Directory.h"

class AbstractBuilder {
	std::unordered_set<fs::path> visited;
protected:
	virtual std::unique_ptr<AbstractFile>buildFile(const fs::path& path);
	virtual std::unique_ptr<AbstractFile>buildDir(const fs::path& path);
	virtual std::unique_ptr<AbstractFile>buildLink(const fs::path& path)= 0;

	std::unique_ptr<AbstractFile> result = nullptr;
public:
	virtual std::unique_ptr<AbstractFile> build(const fs::path& path); 
	std::unique_ptr<AbstractFile>&& getResult();
};