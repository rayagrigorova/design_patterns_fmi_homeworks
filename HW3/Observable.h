#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Observer.h"

class Observable {
protected:
	std::vector<std::unique_ptr<Observer>> subscribers;
public:
	virtual ~Observable() = default;

	void subscribe(std::unique_ptr<Observer>&& o);
	void unsubscribe(size_t ind); 

	void notifySubscribers(const std::string& context) const; 
};