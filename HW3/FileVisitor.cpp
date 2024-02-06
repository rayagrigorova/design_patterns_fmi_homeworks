#include "FileVisitor.h"

void FileVisitor::visitDirectory(const Directory& dir) {
	if (!rootDirPath.has_value()) {
		rootDirPath = dir.getPath();
	}
	const std::vector<std::unique_ptr<AbstractFile>>& children = dir.getChildren();
	for (size_t i = 0; i < children.size(); i++) {
		children[i]->accept(*this);
	}

	if (dir.getPath() == rootDirPath.value()){
		rootDirPath.reset();
	}
}