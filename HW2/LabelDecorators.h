#pragma once

#include <vector>
#include <memory>
#include <random>
#include "Labels.h"
#include "Transformations.h"

class LabelDecoratorBase : public Label {
protected:
    Label& label;

public:
    LabelDecoratorBase(Label& label);

    bool operator==(const Label& other) const override;

    std::string getText() override;

    Label removeDecorator(const LabelDecoratorBase& toRemove);
    static Label removeDecoratorFrom(Label& target, const LabelDecoratorBase& toRemove);
};

class TextTransformationDecorator : public LabelDecoratorBase {
    TextTransformation& t;

public:
    TextTransformationDecorator(Label& label, TextTransformation& t);

    std::string getText() override;

    bool operator==(const Label& other) const override;
};

class RandomTransformationDecorator : public LabelDecoratorBase {
    std::random_device rd;
    std::mt19937 gen;
    std::vector<std::unique_ptr<TextTransformation>> transformations;
    std::uniform_int_distribution<int> distrib;

public:
    RandomTransformationDecorator(Label& label, std::vector<std::unique_ptr<TextTransformation>>& transformations);
    
    std::string getText() override;

    bool operator==(const Label& other) const override;
};
