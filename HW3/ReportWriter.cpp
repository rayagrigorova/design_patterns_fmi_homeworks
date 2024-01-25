#include "ReportWriter.h"

ReportWriter::ReportWriter(std::ostream& os) : os(os){

}

void ReportWriter::visitFile(const File& file) const {
	os << "File to be traversed: " << file.getPath().filename() << " size: " << file.getSize() << "\n";
}