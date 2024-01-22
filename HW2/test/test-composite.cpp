#include <catch2/catch_test_macros.hpp>

#include "CompositeTransformation.h"
#include "Transformations.h"
#include "LabelDecorators.h"

// The first two tests are taken from the example 
TEST_CASE("Composite Transformation - Apply Sequence", "[CompositeTransformation]") {
    SECTION("Apply Capitalize, Decorate, and Replace in Sequence") {
        std::vector<std::unique_ptr<TextTransformation>> transformations;
        // Abc def 
        transformations.push_back(std::make_unique<CapitalizeTransformation>());
        // -={ Abc def }=-
        transformations.push_back(std::make_unique<DecorateTransformation>());
        // -={ Abc def }=-
        transformations.push_back(std::make_unique<ReplaceTransformation>("abc", "def"));

        CompositeTransformation composite(std::move(transformations));
        std::string result = composite.transform("abc def");
        REQUIRE(result == "-={ Abc def }=-");
    }

    SECTION("Rearrange to Replace, Capitalize, and Decorate in Sequence") {
        std::vector<std::unique_ptr<TextTransformation>> transformations;
        transformations.push_back(std::make_unique<ReplaceTransformation>("abc", "def"));
        transformations.push_back(std::make_unique<CapitalizeTransformation>());
        transformations.push_back(std::make_unique<DecorateTransformation>());

        CompositeTransformation composite(std::move(transformations));
        std::string result = composite.transform("abc def");
        REQUIRE(result == "-={ Def def }=-");
    }
}

TEST_CASE("Composite Transformation - Add and Remove Transformations", "[CompositeTransformation]") {
    CompositeTransformation composite;

    SECTION("Add Transformations and Apply") {
        composite.add(std::make_unique<TrimLeftTransformation>());
        composite.add(std::make_unique<TrimRightTransformation>());

        std::string result = composite.transform("   hello world   ");
        REQUIRE(result == "hello world");
    }

    SECTION("Remove Non-Existent Transformation") {
        NormalizeSpaceTransformation nonExistentTransform;
        composite.remove(nonExistentTransform);

        std::string result = composite.transform("   hello   world   ");
        REQUIRE(result == "   hello   world   ");
    }
}

TEST_CASE("Composite Transformation - Order Matters", "[CompositeTransformationOrder]") {
    SECTION("Capitalize After Trim") {
        std::vector<std::unique_ptr<TextTransformation>> transformations;
        transformations.push_back(std::make_unique<TrimLeftTransformation>());
        transformations.push_back(std::make_unique<CapitalizeTransformation>());

        CompositeTransformation composite(std::move(transformations));
        std::string result = composite.transform("   hello world");
        REQUIRE(result == "Hello world");
    }

    SECTION("Trim After Capitalize") {
        std::vector<std::unique_ptr<TextTransformation>> transformations;
        transformations.push_back(std::make_unique<CapitalizeTransformation>());
        transformations.push_back(std::make_unique<TrimLeftTransformation>());

        CompositeTransformation composite(std::move(transformations));
        std::string result = composite.transform("   hello world");
        REQUIRE(result == "hello world");
    }
}

TEST_CASE("Composite Transformation - Empty Transformation List", "[CompositeTransformationEmpty]") {
    CompositeTransformation composite;

    SECTION("Apply Empty Composite Transformation") {
        std::string result = composite.transform("text");
        REQUIRE(result == "text");
    }
}

TEST_CASE("TextTransformationDecorator with CompositeTransformation", "[CompositeDecorator]") {
    SimpleLabel label("  hello this is just some label     ");

    SECTION("Composite - Capitalize and Decorate") {
        std::vector<std::unique_ptr<TextTransformation>> transformations;
        transformations.push_back(std::make_unique<TrimLeftTransformation>());
        transformations.push_back(std::make_unique<CapitalizeTransformation>());
        CompositeTransformation composite(std::move(transformations));
        TextTransformationDecorator decorator(label, composite);

        REQUIRE(decorator.getText() =="Hello this is just some label     ");

        std::vector<std::unique_ptr<TextTransformation>> transformations2;
        transformations2.push_back(std::make_unique<TrimRightTransformation>());
        transformations2.push_back(std::make_unique<DecorateTransformation>());
        CompositeTransformation composite2(std::move(transformations2));
        TextTransformationDecorator decorator2(decorator, composite2);

        REQUIRE(decorator2.getText() == "-={ Hello this is just some label }=-");
        Label* result = decorator2.removeDecorator(decorator);
        REQUIRE(result->getText() == "-={   hello this is just some label }=-");
    }
}

TEST_CASE("TextTransformationDecorator with CompositeTransformation 2", "[CompositeDecorator]") {
    SimpleLabel label("abc   def    abc    def    abc  ");

    SECTION("Composite - Capitalize, nomalize, replace") {
        std::vector<std::unique_ptr<TextTransformation>> transformations;
        transformations.push_back(std::make_unique<CapitalizeTransformation>());
        transformations.push_back(std::make_unique<NormalizeSpaceTransformation>());
        transformations.push_back(std::make_unique<ReplaceTransformation>("abc", "def"));
        CompositeTransformation composite(std::move(transformations));
        TextTransformationDecorator decorator(label, composite);

        REQUIRE(decorator.getText() =="Abc def def def def ");

        std::vector<std::unique_ptr<TextTransformation>> transformations2;
        transformations2.push_back(std::make_unique<TrimRightTransformation>());
        transformations2.push_back(std::make_unique<DecorateTransformation>());
        CompositeTransformation composite2(std::move(transformations2));
        TextTransformationDecorator decorator2(decorator, composite2);

        REQUIRE(decorator2.getText() == "-={ Abc def def def def }=-");
        Label* result = decorator2.removeDecorator(decorator);
        REQUIRE(result->getText() == "-={ abc   def    abc    def    abc }=-");
    }
}
