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
    return label.getText();
}

Label LabelDecoratorBase::removeDecorator(const LabelDecoratorBase& toRemove) {
    if (*this == toRemove) {
        return label;
    }
    if (dynamic_cast<LabelDecoratorBase*>(&label)) {
        label = dynamic_cast<LabelDecoratorBase*>(&label)->removeDecorator(toRemove);
        return *this;
    }
    return *this;
}

Label LabelDecoratorBase::removeDecoratorFrom(Label& target, const LabelDecoratorBase& toRemove) {
    if (dynamic_cast<LabelDecoratorBase*>(&target)) {
        LabelDecoratorBase& ldb = dynamic_cast<LabelDecoratorBase&>(target);
        return ldb.removeDecorator(toRemove);
    }
    return target;
}

TextTransformationDecorator::TextTransformationDecorator(Label& label, TextTransformation& t)
    : t(t), LabelDecoratorBase(label) {}

std::string TextTransformationDecorator::getText() {
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
    Label& label, std::vector<std::unique_ptr<TextTransformation>>& transformations)
    : transformations(transformations), gen(rd()), distrib(0, transformations.size() - 1), LabelDecoratorBase(label) {}

std::string RandomTransformationDecorator::getText() {
    std::string resultValue = LabelDecoratorBase::getText();
    int random_number = distrib(gen);
    return transformations[random_number]->transform(resultValue);
}

bool RandomTransformationDecorator::operator==(const Label& other) const {
    if (!LabelDecoratorBase::operator==(other)) return false;

    const RandomTransformationDecorator* rtd = dynamic_cast<const RandomTransformationDecorator*>(&other);
    if (rtd) {
        return rtd->transformations == transformations;
    }
    return false;
}
