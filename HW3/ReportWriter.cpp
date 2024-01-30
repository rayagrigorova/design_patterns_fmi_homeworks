#include "ReportWriter.h"

ReportWriter::ReportWriter(std::ostream& os) : os(os){

}

void ReportWriter::visitFile(const File& file) {
	os << "File to be traversed: " << fs::relative(file.getPath(), rootDirPath.value()) << " size: " << file.getSize() << std::endl;
}