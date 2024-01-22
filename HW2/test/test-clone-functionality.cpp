#include <catch2/catch_test_macros.hpp>

#include "LabelDecorators.h"
#include "Labels.h"
#include "Transformations.h"
#include "CompositeTransformation.h"

TEST_CASE("Cloning of CapitalizeTransformation", "[clone]") {
    CapitalizeTransformation original;
    auto cloned = original.clone();

    std::string testStr = "example";
    REQUIRE(cloned->transform(testStr) == "Example");
}

TEST_CASE("Cloning of CompositeTransformation", "[clone]") {
    std::vector<std::unique_ptr<TextTransformation>> transformations;
    transformations.push_back(std::make_unique<TrimLeftTransformation>());
    transformations.push_back(std::make_unique<CapitalizeTransformation>());

    CompositeTransformation composite(std::move(transformations));
    auto clonedComposite = composite.clone();

    std::string testStr = " hello";
    REQUIRE(clonedComposite->transform(testStr) == "Hello"); 
}

TEST_CASE("Cloning of TextTransformationDecorator", "[clone]") {
    SimpleLabel label("example");
    CapitalizeTransformation capitalize;
    TextTransformationDecorator original(label, capitalize); 
    auto clonedDecorator = original.clone();

    REQUIRE(clonedDecorator->getText() == "Example");
}

