#include "LabelDecorators.h"

LabelDecoratorBase::LabelDecoratorBase(Label& label) : label(label) {}

bool LabelDecoratorBase::operator==(const Label& other) const {
    const LabelDecoratorBase* otherPtr = dynamic_cast<const LabelDecoratorBase*>(&other);
    if (!otherPtr) {
        return false;
    }
    return otherPtr->label == label;
}

std::string LabelDecoratorBase::getText() {
    // Delegate the getText() operation to the wrapped object
    return label.getText();
}

Label& LabelDecoratorBase::removeDecorator(const LabelDecoratorBase& toRemove) {
    // If this is the decorator to remove 
    if (*this == toRemove) {
        return label;
    }
    // If the label inside the current object is a decorator, try to remove 
    // a decorator further down the chain. 
    if (dynamic_cast<LabelDecoratorBase*>(&label)) {
        label = dynamic_cast<LabelDecoratorBase*>(&label)->removeDecorator(toRemove);
        return *this;
    }
    // This is the case when the label inside the current object is not a decorator,
    // but an actual label. We have reached the end of the list but haven't found the decorator 
    // to remove. 
    return *this;
}

Label& LabelDecoratorBase::removeDecoratorFrom(Label& target, const LabelDecoratorBase& toRemove) {
    // If target refers to a decorator 
    if (dynamic_cast<LabelDecoratorBase*>(&target)) {
        LabelDecoratorBase& ldb = dynamic_cast<LabelDecoratorBase&>(target);
        return ldb.removeDecorator(toRemove);
    }
    // If target isn't a decorator, but an actual label, do nothing 
    return target;
}

TextTransformationDecorator::TextTransformationDecorator(Label& label, TextTransformation& t)
    : t(t), LabelDecoratorBase(label) {}

std::string TextTransformationDecorator::getText() {
    // super::execute 
    std::string resultValue = LabelDecoratorBase::getText();
    return t.transform(resultValue);
}

bool TextTransformationDecorator::operator==(const Label& other) const {
    if (!LabelDecoratorBase::operator==(other)) return false;

    const TextTransformationDecorator* ttd = dynamic_cast<const TextTransformationDecorator*>(&other);
    if (ttd) {
        return ttd->t == t;
    }
    return false;
}

RandomTransformationDecorator::RandomTransformationDecorator(
    Label& label, std::vector<std::unique_ptr<TextTransformation>>&& transformations)
    : distrib(0, transformations.size() - 1), gen(rd()), LabelDecoratorBase(label) {
        // Move the object here. Otherwise, its size can't be used to initialize distrib
        this->transformations = (std::move(transformations));
    }

std::string RandomTransformationDecorator::getText() {
    std::string resultValue = LabelDecoratorBase::getText();
    int random_number = distrib(gen);
    return transformations[random_number]->transform(resultValue);
}

bool RandomTransformationDecorator::operator==(const Label& other) const {
    if (!LabelDecoratorBase::operator==(other)) return false;

    const RandomTransformationDecorator* rtd = dynamic_cast<const RandomTransformationDecorator*>(&other);
    
    if (rtd) {
        if (transformations.size() != rtd->transformations.size()) return false;
        
        for (int i = 0; i < transformations.size(); ++i) {
            if (!(*transformations[i] == *rtd->transformations[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}
