#include "Directory.h"
#include "FileVisitor.h"

Directory::Directory(const fs::path& path) : AbstractFile(path){
	
}

void Directory::add(std::unique_ptr<AbstractFile>&& elem) {
	// Don't add null pointers.
	// The passed element could be a null pointer if buildDir()
	// returns nullptr (returning nullptr is done to avoid creating cycles).
	if (elem == nullptr) {
		return;
	}
	cachedSize += elem->getSize();
	children.push_back(std::move(elem));
}

const std::vector<std::unique_ptr<AbstractFile>>& Directory::getChildren() const{
	return children;
}

std::uintmax_t Directory::getSize() const {
	return cachedSize;
}

void Directory::accept(FileVisitor& v) const{
	v.visitDirectory(*this);
}