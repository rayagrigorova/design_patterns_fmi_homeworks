#pragma once

#include "FileVisitor.h"

class ReportWriter : public FileVisitor {
	std::ostream& os;
public:
	ReportWriter(std::ostream& os);

	void visitFile(File& file) const override;
};