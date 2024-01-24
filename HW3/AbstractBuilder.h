#pragma once

#include "File.h"
#include "Directory.h"

class AbstractBuilder {
protected:
	virtual std::unique_ptr<AbstractFile>buildFile(const fs::path& path) const;
	virtual std::unique_ptr<AbstractFile>buildDir(const fs::path& path) const;
	virtual std::unique_ptr<AbstractFile>buildLink(const fs::path& path) const = 0;

	std::unique_ptr<AbstractFile> result = nullptr;
public:
	virtual std::unique_ptr<AbstractFile> build(const fs::path& path); 
	std::unique_ptr<AbstractFile>&& getResult();
};