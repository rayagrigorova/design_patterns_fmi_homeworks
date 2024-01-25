#include "FileVisitor.h"

void FileVisitor::visitDirectory(const Directory& dir) const {
	const std::vector<std::unique_ptr<AbstractFile>>& children = dir.getChildren();
	for (size_t i = 0; i < children.size(); i++) {
		children[i]->accept(*this);
	}
}