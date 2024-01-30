#pragma once

#include <filesystem>

class FileVisitor;

// this creates an alias for the namespace 
namespace fs = std::filesystem;

class AbstractFile {
protected:
	// Each abstrach file (directory/file) should have a path
	fs::path path;
public:
	virtual ~AbstractFile() = default;
	AbstractFile() = default;
	AbstractFile(const fs::path& path);

	virtual std::uintmax_t getSize() const = 0;
	const fs::path& getPath() const;

	// use double dispatch to execute the proper visitor method on the current instance
	virtual void accept(FileVisitor& v) const = 0;
};