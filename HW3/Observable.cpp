#include <iostream>

#include "Observable.h"
#include "Observer.h"

void Observable::subscribe(std::unique_ptr<Observer>&& o) {
	subscribers.push_back(std::move(o));
}

void Observable::unsubscribe(size_t ind) {
	if (ind >= subscribers.size()) {
		std::cerr << "Invalid delete index for subscriber";
		return;
	}
	subscribers.erase(subscribers.begin() + ind);
}

void Observable::notifySubscribers(const std::string& context) const {
	for (size_t i = 0; i < subscribers.size(); i++) {
		subscribers[i]->update(context);
	}
}
