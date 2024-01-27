#pragma once

#include "Observer.h"

class ProgressReporter : public Observer{
public:
	virtual void update(const std::string& context) const override;
};
