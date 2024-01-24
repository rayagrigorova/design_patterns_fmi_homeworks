#include "File.h"

#include <iostream>

File::File(const fs::path& path) : AbstractFile(path){
	try {
		std::uintmax_t fileSize = fs::file_size(path);
		size = fileSize; 
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "An error ocurred: " << e.what() << std::endl;
	}
}

std::uintmax_t File::getSize() const {
	return size;
}

void File::accept(const FileVisitor& v) {
	v.visitFile(*this);
}
