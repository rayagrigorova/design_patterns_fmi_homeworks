#pragma once

#include <string>

class Observable;

class Observer {
public:
	virtual void update(const Observable& sender, const std::string& context) = 0;
};