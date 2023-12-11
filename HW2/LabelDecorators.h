#pragma once

#include <vector>
#include <memory> // unique_ptr
#include <random> // random_device, mt19937, uniform_int_distribution

#include "Labels.h"
#include "Transformations.h"

// What should I use instead of Class decoratorType? 
// const std::type_info& decoratorType or a simple enum?
//enum class DecoratorType {
//	///
//};

// I am adding all decorators to one file to prevent scattering short pieces of code 

// A base class for all decorators 
class LabelDecoratorBase : public Label {
protected:
	Label& label;
public:
	LabelDecoratorBase(Label& label) : label(label){}

	// This is possible since Label is polymorphic 
	virtual bool operator==(const Label& other) const{
		if (dynamic_cast<const LabelDecoratorBase*>(&other)) {
			const LabelDecoratorBase& otherDecorator = dynamic_cast<const LabelDecoratorBase&>(other);
		}

		return Label::operator==(other);
	}
	
	std::string getText() override {
		// Delegate work to wrapped object
		label.getText();
	}

	Label removeDecorator(const LabelDecoratorBase& toRemove) {
		// If this is the decorator to remove, return the wrapped label
		
		// If the current decorator is the one to be removed 
		if (*this == toRemove) {
			return label;
		}
		// If the label itself is a decorator 
		if (dynamic_cast<LabelDecoratorBase*>(&label)) {
			label = dynamic_cast<LabelDecoratorBase*>(&label)->removeDecorator(toRemove);
			// keep current object on top of the list
			return *this;
		}
		// this is the case when the label is not a decorator 
		return *this;
	}

	static Label removeDecoratorFrom(Label& target, const LabelDecoratorBase& toRemove) {
		// The label object is a decorator 
		if (dynamic_cast<LabelDecoratorBase*>(&target)) {
				LabelDecoratorBase& ldb = dynamic_cast<LabelDecoratorBase&>(target);
				// delegate the work for removing to the decorator 
				return ldb.removeDecorator(toRemove);
		}
		// else: the label is just a plain label with some text, nothing to do 
	}
};

// This class applies a single transformation 
class TextTransformationDecorator : public LabelDecoratorBase {
	TextTransformation& t;
public:
	TextTransformationDecorator(Label& label, TextTransformation& t) : t(t), LabelDecoratorBase(label) {}
	
	virtual std::string getText() override {
		// Save the result of calling super::getText() in a variable 
		std::string resultValue = LabelDecoratorBase::getText();
		return t.transform(resultValue);
	}

	bool operator==(const Label& other) const override {
		if (!LabelDecoratorBase::operator==(other))return false;
		const TextTransformationDecorator* ttd = dynamic_cast<const TextTransformationDecorator*>(&other);

		if (ttd) {
			return ttd->t == t;
		}
		return false;
	}
};

class RandomTransformationDecorator : public LabelDecoratorBase {
	std::random_device rd; 
	std::mt19937 gen;
	std::vector<std::unique_ptr<TextTransformation>> transformations;
	std::uniform_int_distribution<int> distrib; 

public:
	RandomTransformationDecorator(Label& label, std::vector<std::unique_ptr<TextTransformation>>& transformations) : transformations(transformations),
		gen(rd()), distrib(0, transformations.size() - 1), LabelDecoratorBase(label){}

	virtual std::string getText() override {
		std::string resultValue = LabelDecoratorBase::getText();
		int random_number = distrib(gen);
		return transformations[random_number]->transform(resultValue);
	}

	bool operator==(const Label& other) const override {
		if (!LabelDecoratorBase::operator==(other))return false;
		const RandomTransformationDecorator* rtd = dynamic_cast<const RandomTransformationDecorator*>(&other);

		if (rtd) {
			// Can I compare vectors like this?
			return rtd->transformations == transformations;
		}
		return false;
	}
};
