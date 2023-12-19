#include "LabelDecorators.h"

LabelDecoratorBase::LabelDecoratorBase(Label* label) : label(label){}

LabelDecoratorBase::~LabelDecoratorBase() {
    // since LabelDecoratorBase is not the owner of the pointer, just set it to null
    label = nullptr;
}

bool LabelDecoratorBase::equals(const LabelDecoratorBase& other) const {
    if (typeid(*this) != typeid(other)) {
        return false;
    }
    // If the types of the decorators are the same, then the decorators are equal 
    // This is the default behaviour of this function. It needs to be extended for concrete decorators. 
    return true;
}

std::string LabelDecoratorBase::getText() {
    // since label isn't ownership of LabelDecoratorBase, it could be prematurely deleted 
    if (label == nullptr) {
        return "";
    }
    // Delegate the getText() operation to the wrapped object
    return label->getText();
}

Label* LabelDecoratorBase::removeDecorator(const LabelDecoratorBase& toRemove) {
    // if this is the decorator to remove 
    if (toRemove.equals(*this)) {
        return label; 
    }

    // Check if the wrapped label is also a decorator
    LabelDecoratorBase* decorator = dynamic_cast<LabelDecoratorBase*>(label);
    if (decorator) {
        label = decorator->removeDecorator(toRemove);
    }

    return this; // Return this decorator
}

Label* removeDecoratorFrom(Label& target, const LabelDecoratorBase& toRemove) {
    // If target refers to a decorator 
    LabelDecoratorBase* ptr = dynamic_cast<LabelDecoratorBase*>(&target); 
    if (ptr) {
        return ptr->removeDecorator(toRemove);
    }
    // If target isn't a decorator, but an actual label, do nothing 
    return nullptr;
}

TextTransformationDecorator::TextTransformationDecorator(Label* label, TextTransformation& t)
    : LabelDecoratorBase(label), t(t){}

std::string TextTransformationDecorator::getText() {
    // super::execute 
    std::string resultValue = LabelDecoratorBase::getText();
    return t.transform(resultValue);
}

bool TextTransformationDecorator::equals(const LabelDecoratorBase& other) const {
    const TextTransformationDecorator* ttd = dynamic_cast<const TextTransformationDecorator*>(&other);
    if (ttd) {
        // compare the transformations 
        return ttd->t.equals(t);
    }
    return false;
}

RandomTransformationDecorator::RandomTransformationDecorator(Label* label, 
    std::vector<std::unique_ptr<TextTransformation>>&& transformations)
    : distrib(0, transformations.size() - 1), gen(rd()), LabelDecoratorBase(label) {
        // Move the object here. Otherwise, its size can't be used to initialize distrib
        this->transformations = (std::move(transformations));
    }

std::string RandomTransformationDecorator::getText() {
    std::string resultValue = LabelDecoratorBase::getText();
    int random_number = distrib(gen);
    return transformations[random_number]->transform(resultValue);
}

bool RandomTransformationDecorator::equals(const LabelDecoratorBase& other) const {
    const RandomTransformationDecorator* rtd = dynamic_cast<const RandomTransformationDecorator*>(&other);
    // compare the vectors of transformations 
    if (rtd) {
        if (transformations.size() != rtd->transformations.size()) return false;
        
        for (int i = 0; i < transformations.size(); ++i) {
            if (!(transformations[i]->equals(*rtd->transformations[i]))) {
                return false;
            }
        }
        return true;
    }
    return false;
}
