#include "AbstractBuilder.h"

std::unique_ptr<File> AbstractBuilder::buildFile(const fs::path& path) {
	return std::make_unique<File>(path);
}

namespace {
	bool isWindowsShortcut(const fs::path& path) {
		return path.extension() == ".lnk";
	}
}

std::unique_ptr<Directory> AbstractBuilder::buildDir(const fs::path& path) {
	if (fs::is_directory(path)) {
		std::unique_ptr<Directory> directory = std::make_unique<Directory>(path);
		for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
			if (fs::is_symlink(entry.path()) || isWindowsShortcut(entry.path())) {
				directory->add(buildLink(entry.path()));
			}
			else if (fs::is_directory(entry.path())) {
				directory->add(buildDir(entry.path()));
			}
			else {
				directory->add(buildFile(entry.path()));
			}
		}
		visited.insert(directory->getPath());
		return directory;
	}
	return nullptr;
}
