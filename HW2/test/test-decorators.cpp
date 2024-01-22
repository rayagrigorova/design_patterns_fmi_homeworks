#include <catch2/catch_test_macros.hpp>
#include "LabelDecorators.h"
#include "Transformations.h"
#include "Labels.h"

TEST_CASE("TextTransformationDecorator with CapitalizeTransformation") {
    SimpleLabel simpleLabel("test label");
    CapitalizeTransformation capitalizeTransformation;

    TextTransformationDecorator decorator(simpleLabel, capitalizeTransformation);
    REQUIRE(decorator.getText() == "Test label");
}

TEST_CASE("RandomTransformationDecorator with multiple transformations") {
    SimpleLabel simpleLabel("test label");
    auto transformation1 = std::make_unique<CapitalizeTransformation>();
    auto transformation2 = std::make_unique<TrimLeftTransformation>();

    std::vector<std::unique_ptr<TextTransformation>> transformations;
    transformations.push_back(std::move(transformation1));
    transformations.push_back(std::move(transformation2));

    RandomTransformationDecorator randomDecorator(simpleLabel, std::move(transformations));

    std::string transformedText = randomDecorator.getText();
    REQUIRE((transformedText == "Test label" || transformedText == "test label"));
}

TEST_CASE("RemoveDecorator functionality") {
    SimpleLabel simpleLabel("test label");
    CapitalizeTransformation capitalizeTransformation;

    TextTransformationDecorator decorator(simpleLabel, capitalizeTransformation);
    TextTransformationDecorator secondDecorator(decorator, capitalizeTransformation);

    // Dereference the pointer to get a reference
    Label& result = *LabelDecoratorBase::removeDecoratorFrom(secondDecorator, decorator);
    REQUIRE(result.getText() == "Test label");
}

TEST_CASE("Decorator Tests") {
    SECTION("TextTransformationDecorator") {
        SimpleLabel simpleLabel("Hello");
        CapitalizeTransformation capitalize;
        TextTransformationDecorator decorator(simpleLabel, capitalize);

        REQUIRE(decorator.getText() == "Hello");

        TrimLeftTransformation trimLeft;
        TextTransformationDecorator decorator2(decorator, trimLeft);
        REQUIRE(decorator2.getText() == "Hello");
    }
}

TEST_CASE("RemoveDecorator functionality with chained decorators") {
    SimpleLabel simpleLabel("test label      ");
    CapitalizeTransformation capitalizeTransformation;
    TrimRightTransformation trimTransformation;

    TextTransformationDecorator decorator(simpleLabel, trimTransformation);
    TextTransformationDecorator secondDecorator(decorator, capitalizeTransformation);

    REQUIRE(secondDecorator.getText() == "Test label");
    
    Label& result = *LabelDecoratorBase::removeDecoratorFrom(secondDecorator, decorator);
    REQUIRE(result.getText() == "Test label      ");
}
