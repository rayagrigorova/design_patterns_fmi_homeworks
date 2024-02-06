#pragma once

#include <memory>
#include <string>
#include <vector>

class Observer;

class Observable {
protected:
	std::vector<std::shared_ptr<Observer>> subscribers;
public:
	virtual ~Observable() = default;

	virtual void subscribe(std::shared_ptr<Observer> o);
	virtual void unsubscribe(size_t ind); 

	virtual void notifySubscribers(const std::string& context) const; 
};