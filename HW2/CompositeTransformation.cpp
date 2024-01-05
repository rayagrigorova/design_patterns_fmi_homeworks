#include <iostream>

#include "CompositeTransformation.h"

CompositeTransformation::CompositeTransformation(std::vector<std::unique_ptr<TextTransformation>>&& children) noexcept : children(std::move(children)) {

}

void CompositeTransformation::add(std::unique_ptr<TextTransformation>&& tt) {
	children.push_back(std::move(tt));
}

void CompositeTransformation::remove(const TextTransformation& tt) {
	for (int i = 0; i < children.size(); i++) {
		if (children[i]->equals(tt)) {
			children.erase(children.begin() + i);
			return;
		}
	}
	std::cerr << "The transformation to be deleted wasn't found.";
}

std::string CompositeTransformation::transform(std::string text) const {
	for (const std::unique_ptr<TextTransformation>& child : children) {
		text = child->transform(text);
	}
	return text;
}

bool CompositeTransformation::equals(const TextTransformation& other) const {
	if (typeid(*this) != typeid(other)) {
		return false;
	}
	// For two composite transformations to be equal, they should contain the same 
	// transformations in the same order
	const CompositeTransformation* ptr = dynamic_cast<const CompositeTransformation*>(&other);
	if (ptr->children.size() != children.size()) {
		return false;
	}
	
	for (int i = 0; i < children.size(); i++) {
		if (!(ptr->children[i]->equals(*children[i]))){
			return false;
		}
	}
	return true;
}

std::unique_ptr<TextTransformation> CompositeTransformation::clone() const {
	std::vector<std::unique_ptr<TextTransformation>> clonedChildren;
	clonedChildren.reserve(children.size());

	for (const auto& child : children) {
		clonedChildren.push_back(child->clone());
	}

	return std::make_unique<CompositeTransformation>(std::move(clonedChildren));
}

