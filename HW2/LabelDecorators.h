#pragma once

#include <vector>
#include <memory>
#include <random>
#include "Labels.h"
#include "Transformations.h"

// Label is the common class for both labels and decorators 
// The following class is a base decorator 
class LabelDecoratorBase : public Label {
protected:
    Label* label = nullptr;

    void free();
    void copyFrom(const LabelDecoratorBase& other);
    void moveFrom(LabelDecoratorBase&& other);

public:
    LabelDecoratorBase(Label* label);

    // Big 6 
    LabelDecoratorBase() = default;
    LabelDecoratorBase(const LabelDecoratorBase& other);
    LabelDecoratorBase(LabelDecoratorBase&& other) noexcept;

    LabelDecoratorBase& operator=(const LabelDecoratorBase& other);
    LabelDecoratorBase& operator=(LabelDecoratorBase&& other) noexcept;

    ~LabelDecoratorBase();

    virtual bool equals(const LabelDecoratorBase& other) const;

    // This is the operation that each class inheriting from Label should implement
    std::string getText() override;

   Label* removeDecorator(const LabelDecoratorBase& toRemove);
   static Label* removeDecoratorFrom(Label& target, const LabelDecoratorBase& toRemove);
};

// The following classes are concrete decorators 

class TextTransformationDecorator : public LabelDecoratorBase {
    // Making use of the Strategy pattern 
    TextTransformation& t;

public:
    TextTransformationDecorator(Label* label, TextTransformation& t);

    std::string getText() override;

    bool equals(const LabelDecoratorBase& other) const override;
};

class RandomTransformationDecorator : public LabelDecoratorBase {
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> distrib;
    std::vector<std::unique_ptr<TextTransformation>> transformations;

public:
    RandomTransformationDecorator(Label* label, std::vector<std::unique_ptr<TextTransformation>>&& transformations);
    
    std::string getText() override;

    bool equals(const LabelDecoratorBase& other) const override;
};
