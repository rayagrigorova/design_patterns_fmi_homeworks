#pragma once

#include "Observer.h"
#include <string>

class ProgressReporter : public Observer{
public:
	virtual void update(const Observable& sender, const std::string& context) const override;
};
