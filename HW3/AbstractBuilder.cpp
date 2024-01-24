#include "AbstractBuilder.h"

std::unique_ptr<AbstractFile> AbstractBuilder::buildFile(const fs::path& path) {
	return std::make_unique<File>(path);
}

namespace {
	bool isWindowsShortcut(const fs::path& path) {
		return path.extension() == ".lnk";
	}
}

std::unique_ptr<AbstractFile> AbstractBuilder::buildDir(const fs::path& path) {
	if (fs::is_symlink(path) || isWindowsShortcut(path)) {
		// Check if the symbolic link/shortcut is about to create 
		// a cycle. If yes, then don't add it. 
		return buildLink(path);
	}
	
	if (fs::is_directory(path)) {
		std::unique_ptr<Directory> directory = std::make_unique<Directory>(path);
		for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
			directory->add(buildDir(entry.path()));
		}
		visited.insert(directory);
		return directory;
	}
	return buildFile(path);
}

std::unique_ptr<AbstractFile> AbstractBuilder::build(const fs::path& path) {
	buildDir(path);
}

std::unique_ptr<AbstractFile>&& AbstractBuilder::getResult() {
	return std::move(result);
}
