#pragma once

#include "AbstractBuilder.h"

class FollowBuilder : public AbstractBuilder {
protected:
	virtual std::unique_ptr<AbstractFile>buildLink(const fs::path& path) override;
};