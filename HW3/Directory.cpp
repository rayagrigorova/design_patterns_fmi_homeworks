#include "Directory.h"
#include "File.h"


Directory::Directory(const fs::path& path) : AbstractFile(path){
	
}

void Directory::add(std::unique_ptr<AbstractFile>&& elem) {
	// No need to recalculate the size of the whole directory
	cachedSize += elem->getSize();
	children.push_back(std::move(elem));
}

const std::vector<std::unique_ptr<AbstractFile>>& Directory::getChildren() const {
	return children;
}

std::uintmax_t Directory::getSize() const {
	return cachedSize;
}

void Directory::accept(const FileVisitor& v) {
	v.visitDirectory(*this);
}