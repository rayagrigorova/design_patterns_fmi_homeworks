#pragma once

#include "AbstractBuilder.h"

class NoFollowBuilder : public AbstractBuilder {
protected:
	virtual std::unique_ptr<AbstractFile>buildLink(const fs::path& path) override;
};