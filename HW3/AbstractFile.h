#pragma once

#include <filesystem>

class FileVisitor;

// This creates an alias for the namespace 
namespace fs = std::filesystem;

class AbstractFile {
protected:
	// Each abstract file (directory/file) should have a path
	fs::path path;
public:
	virtual ~AbstractFile() = default;
	AbstractFile() = default;
	AbstractFile(const fs::path& path);

	virtual std::uintmax_t getSize() const = 0;
	const fs::path& getPath() const;

	// Use double dispatch to execute the proper visitor method on the current instance
	virtual void accept(FileVisitor& v) const = 0;
};