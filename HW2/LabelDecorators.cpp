#include "LabelDecorators.h"

LabelDecoratorBase::LabelDecoratorBase(Label& label) {
    this->label = label.clone();
}

LabelDecoratorBase::~LabelDecoratorBase() {
    free();
}

LabelDecoratorBase::LabelDecoratorBase(const LabelDecoratorBase& other) {
    copyFrom(other);
}

LabelDecoratorBase::LabelDecoratorBase(LabelDecoratorBase&& other) noexcept{
    moveFrom(std::move(other));
}

LabelDecoratorBase& LabelDecoratorBase::operator=(const LabelDecoratorBase& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

LabelDecoratorBase& LabelDecoratorBase::operator=(LabelDecoratorBase&& other) noexcept{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void LabelDecoratorBase::free() {
    delete label;
    label = nullptr;
}

void LabelDecoratorBase::copyFrom(const LabelDecoratorBase& other){
    if (other.label == nullptr) {
        label = nullptr;
        return;
    }
    label = other.label->clone();
}

void LabelDecoratorBase::moveFrom(LabelDecoratorBase&& other) {
    label = other.label;
    other.label = nullptr;
}

// If the types of the decorators are the same, then the decorators are equal 
// This is the default behaviour of this function. It needs to be extended for concrete decorators. 
bool LabelDecoratorBase::equals(const LabelDecoratorBase& other) const {
    if (typeid(*this) != typeid(other)) {
        return false;
    }
    return true;
}

std::string LabelDecoratorBase::getText() {
    if (label == nullptr) {
        return "";
    }
    // Delegate the getText() operation to the wrapped object
    return label->getText();
}

// This function creates a copy of the current decorator (without adding 'toRemove' to it) 
Label* LabelDecoratorBase::removeDecorator(const LabelDecoratorBase& toRemove) {
    // If this is the decorator to remove 
    if (toRemove.equals(*this)) {
        Label* cloned = label->clone(); 
        return cloned;
    }

    // Check if the wrapped label is also a decorator
    LabelDecoratorBase* decorator = dynamic_cast<LabelDecoratorBase*>(label);
    LabelDecoratorBase* copyThis = dynamic_cast<LabelDecoratorBase*>(this->clone());

    if (decorator) {
        copyThis->label = decorator->removeDecorator(toRemove);
    }

    // This is done in the cases if the label is a decorator (to keep it on top of the list) 
    // or if the label is text and not a decorator
    return copyThis;
}

Label* LabelDecoratorBase::removeDecoratorFrom(Label& target, const LabelDecoratorBase& toRemove) {
    // If 'target' refers to a decorator 
    LabelDecoratorBase* ptr = dynamic_cast<LabelDecoratorBase*>(&target); 
    if (ptr) {
        return ptr->removeDecorator(toRemove);
    }
    // If target isn't a decorator, but an actual label
    return target.clone(); 
}

Label* LabelDecoratorBase::clone() const {
    return new LabelDecoratorBase(*this);
}

TextTransformationDecorator::TextTransformationDecorator(Label& label, const TextTransformation& t)
    : LabelDecoratorBase(label), t(t){}

std::string TextTransformationDecorator::getText() { 
    std::string resultValue = LabelDecoratorBase::getText(); // super::execute
    return t.transform(resultValue);
}

bool TextTransformationDecorator::equals(const LabelDecoratorBase& other) const {
    const TextTransformationDecorator* ttd = dynamic_cast<const TextTransformationDecorator*>(&other);
    if (ttd) {
        // Compare the transformations 
        return ttd->t.equals(t);
    }
    return false;
}

Label* TextTransformationDecorator::clone() const {
    return new TextTransformationDecorator(*this);
}

TextTransformationDecorator::TextTransformationDecorator(const TextTransformationDecorator& other) : LabelDecoratorBase(other), t(other.t){

}

RandomTransformationDecorator::RandomTransformationDecorator(Label& label, 
    std::vector<std::unique_ptr<TextTransformation>>&& transformations)
    : distrib(0, transformations.size() - 1), gen(rd()), LabelDecoratorBase(label) {
        // Move the vector here. Otherwise, the vector's size can't be used to initialize distrib.
        this->transformations = (std::move(transformations));
    }

/*  Since objects providing random numbers 
    don't have copy constructors, they will
    simply be initialized appropriately.
*/
RandomTransformationDecorator::RandomTransformationDecorator(const RandomTransformationDecorator& other)
    : LabelDecoratorBase(other), distrib(0, other.transformations.size() - 1), gen(rd()) {
    transformations.resize(other.transformations.size());

    for (int i = 0; i < other.transformations.size(); i++) {
        transformations[i] = other.transformations[i]->clone();
    }
}

std::string RandomTransformationDecorator::getText() {
    std::string resultValue = LabelDecoratorBase::getText(); // super::execute
    int random_number = distrib(gen);
    return transformations[random_number]->transform(resultValue);
}

bool RandomTransformationDecorator::equals(const LabelDecoratorBase& other) const {
    const RandomTransformationDecorator* rtd = dynamic_cast<const RandomTransformationDecorator*>(&other);
    if (rtd) {
        // Compare the vectors of transformations 
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

Label* RandomTransformationDecorator::clone() const {
    return new RandomTransformationDecorator(*this);
}
