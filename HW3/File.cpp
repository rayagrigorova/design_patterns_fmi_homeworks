#include "File.h"
#include "FileVisitor.h"

#include <iostream>

File::File(const fs::path& path) : AbstractFile(path){
	try {
		std::uintmax_t fileSize = fs::file_size(path);
		size = fileSize; 
	}
	// The function file_size() could throw an error (for example, if the file doesn't exist)
	catch (const fs::filesystem_error& e) {
		std::cerr << "An error occurred: " << e.what() << std::endl;
	}
}

std::uintmax_t File::getSize() const {
	return size;
}

// 'Tell' the visitor that the object it's visiting is a file. 
void File::accept(FileVisitor& v) const{
	v.visitFile(*this);
}
