#include <catch2/catch_test_macros.hpp>
#include "LabelDecorators.h"

TEST_CASE("SimpleLabel Tests", "[SimpleLabel]") {
    SimpleLabel label("Test Label");

    SECTION("getText returns correct text") {
        REQUIRE(label.getText() == "Test Label");
    }
}

TEST_CASE("TextTransformationDecorator Tests", "[TextTransformationDecorator]") {
    SimpleLabel baseLabel("test");
    CapitalizeTransformation capitalizeTransform;
    TextTransformationDecorator decorator(baseLabel, capitalizeTransform);

    SECTION("getText returns transformed text") {
        REQUIRE(decorator.getText() == "Test"); // Assuming CapitalizeTransformation capitalizes first letter
    }

    SECTION("equals returns true for same transformation") {
        TextTransformationDecorator anotherDecorator(baseLabel, capitalizeTransform);
        REQUIRE(decorator.equals(anotherDecorator) == true);
    }
}

TEST_CASE("RandomTransformationDecorator Tests", "[RandomTransformationDecorator]") {
    SimpleLabel baseLabel("test");
    std::vector<std::unique_ptr<TextTransformation>> transformations;
    transformations.push_back(std::make_unique<CapitalizeTransformation>());
    transformations.push_back(std::make_unique<TrimLeftTransformation>());

    RandomTransformationDecorator randomDecorator(baseLabel, std::move(transformations));

    SECTION("getText returns one of the transformations") {
        std::string transformedText = randomDecorator.getText();
        // Check if the result is one of the expected transformations
        REQUIRE((transformedText == "Test" || transformedText == "test"));
    }
}

TEST_CASE("RichLabel Functionality", "[RichLabel]") {
    RichLabel richLabel("Rich Text", "blue", "Arial", 12);

    SECTION("RichLabel Properties") {
        REQUIRE(richLabel.getText() == "Rich Text");
        REQUIRE(richLabel.color == "blue");
        REQUIRE(richLabel.font == "Arial");
        REQUIRE(richLabel.fontSize == 12);
    }
}

TEST_CASE("LabelDecoratorBase Equality", "[LabelDecoratorBase]") {
    SimpleLabel baseLabel("base");
    CapitalizeTransformation capTransform;
    TextTransformationDecorator capDecorator(baseLabel, capTransform);

    SECTION("Different Decorators Are Not Equal") {
        TrimLeftTransformation trimTransform;
        TextTransformationDecorator trimDecorator(baseLabel, trimTransform);
        REQUIRE_FALSE(capDecorator.equals(trimDecorator));
    }
}

TEST_CASE("Decorator Chain Functionality", "[DecoratorChain]") {
    SimpleLabel baseLabel("  hello world  ");
    CapitalizeTransformation capTransform;
    TrimLeftTransformation trimLeftTransform;
    TrimRightTransformation trimRightTransform;

    // "hello world  "
    TextTransformationDecorator trimLeftDecorator(baseLabel, trimLeftTransform);
    REQUIRE(trimLeftDecorator.getText() == "hello world  ");
    // "Hello world  "
    TextTransformationDecorator capDecorator(trimLeftDecorator, capTransform);
    REQUIRE(capDecorator.getText() == "Hello world  ");
    // "hello world"
    TextTransformationDecorator trimRightDecorator(trimLeftDecorator, trimRightTransform);
    REQUIRE(trimRightDecorator.getText() == "hello world");
}

TEST_CASE("Decorator Removal in Complex Chains", "[DecoratorRemoval]") {
    SimpleLabel baseLabel(" data ");
    TrimLeftTransformation trimLeft;
    TrimRightTransformation trimRight;
    CapitalizeTransformation capitalize;

    TextTransformationDecorator leftDecorator(baseLabel, trimLeft);
    TextTransformationDecorator rightDecorator(leftDecorator, trimRight);
    TextTransformationDecorator capitalizeDecorator(rightDecorator, capitalize);

    SECTION("Remove Inner Decorator") {
        Label* afterRemoval = LabelDecoratorBase::removeDecoratorFrom(capitalizeDecorator, leftDecorator);
        REQUIRE(afterRemoval->getText() == " data");
    }
    SECTION("Remove Inner Decorator 2") {
        Label* afterRemoval = LabelDecoratorBase::removeDecoratorFrom(capitalizeDecorator, rightDecorator);
        REQUIRE(afterRemoval->getText() == "Data ");
    }
    SECTION("Remove Inner Decorator 3") {
        Label* afterRemoval = LabelDecoratorBase::removeDecoratorFrom(capitalizeDecorator, capitalizeDecorator);
        REQUIRE(afterRemoval->getText() == "data");
    }
}

TEST_CASE("Decorator Removal Tests", "[DecoratorRemoval]") {
    SECTION("Removing Existing Decorator") {
        SimpleLabel label("abc def");
        ReplaceTransformation replace("abc", "def");
        CapitalizeTransformation capitalize;
        DecorateTransformation decorate;

        // "def def"
        TextTransformationDecorator replaceDecorator(label, replace);
        // "Def def"
        TextTransformationDecorator capitalizeDecorator(replaceDecorator, capitalize);
        // "-={ Def def }=-"
        TextTransformationDecorator decorateDecorator(capitalizeDecorator, decorate);

        Label* result = LabelDecoratorBase::removeDecoratorFrom(decorateDecorator, capitalizeDecorator);
        REQUIRE(result->getText() == "-={ def def }=-");
    }

    SECTION("Removing Non-Existent Decorator") {
        SimpleLabel label("abc def");
        ReplaceTransformation replace("abc", "def");
        CapitalizeTransformation capitalize;

        TextTransformationDecorator replaceDecorator(label, replace);
        TextTransformationDecorator capDec(replaceDecorator, capitalize);

        Label* result = LabelDecoratorBase::removeDecoratorFrom(capDec, capDec);
        REQUIRE(result->getText() == "def def");
    }

    SECTION("Removing Top Decorator") {
        SimpleLabel label("abc def");
        ReplaceTransformation replace("abc", "def");

        TextTransformationDecorator replaceDecorator(label, replace);

        Label* result = LabelDecoratorBase::removeDecoratorFrom(replaceDecorator, replaceDecorator);
        REQUIRE(result->getText() == "abc def");
    }

    SECTION("Removing Bottom Decorator") {
        SimpleLabel label("abc def");
        ReplaceTransformation replace("abc", "def");
        DecorateTransformation decorate;

        TextTransformationDecorator replaceDecorator(label, replace);
        TextTransformationDecorator decorateDecorator(replaceDecorator, decorate);

        Label* result = LabelDecoratorBase::removeDecoratorFrom(decorateDecorator, replaceDecorator);
        REQUIRE(result->getText() == "-={ abc def }=-");
    }

    SECTION("Removing Decorator From Single-Decorator Stack") {
        SimpleLabel label("abc def");
        ReplaceTransformation replace("abc", "def");

        TextTransformationDecorator replaceDecorator(label, replace);

        Label* result = LabelDecoratorBase::removeDecoratorFrom(replaceDecorator, replaceDecorator);
        REQUIRE(result->getText() == "abc def");
    }
}

TEST_CASE("Chained Decorator Removal - Complex Sequence", "[ComplexDecoratorSequenceRemoval]") {
    SimpleLabel baseLabel("abc def");
    CapitalizeTransformation capitalizeTransform;
    TrimLeftTransformation trimLeftTransform;
    DecorateTransformation decorateTransform;

    TextTransformationDecorator firstDecorator(baseLabel, trimLeftTransform);
    // "Abc def"
    TextTransformationDecorator secondDecorator(firstDecorator, capitalizeTransform);
    // "-={ Abc def }=-"
    TextTransformationDecorator thirdDecorator(secondDecorator, decorateTransform);

    SECTION("Remove Middle Decorator") {
        Label* result = LabelDecoratorBase::removeDecoratorFrom(thirdDecorator, secondDecorator);
        REQUIRE(result->getText() == "-={ abc def }=-");
    }

    SECTION("Remove Last Decorator") {
        Label* result = LabelDecoratorBase::removeDecoratorFrom(thirdDecorator, thirdDecorator);
        REQUIRE(result->getText() == "Abc def");
    }

}

TEST_CASE("Nested Decorator Removal - Verify Integrity", "[NestedDecoratorIntegrityCheck]") {
    SimpleLabel baseLabel("   example   ");
    TrimRightTransformation trimRightTransform;
    NormalizeSpaceTransformation normalizeSpaceTransform;

    // "   example"
    TextTransformationDecorator trimRightDecorator(baseLabel, trimRightTransform);
    // " example"
    TextTransformationDecorator normalizeSpaceDecorator(trimRightDecorator, normalizeSpaceTransform);

    SECTION("Remove Non-Existent TrimLeft Decorator") {
        TrimLeftTransformation trimLeftTransform;
        TextTransformationDecorator trimLeftDecorator(normalizeSpaceDecorator, trimLeftTransform);
        Label* result = LabelDecoratorBase::removeDecoratorFrom(normalizeSpaceDecorator, trimLeftDecorator);
        REQUIRE(result->getText() == " example");
    }

    SECTION("Retain NormalizeSpace After Removing TrimRight") {
        Label* result = LabelDecoratorBase::removeDecoratorFrom(normalizeSpaceDecorator, trimRightDecorator);
        REQUIRE(result->getText() == " example ");
    }
}

TEST_CASE("Decorator Stack Manipulation - Add and Remove", "[DecoratorStackManipulation]") {
    SimpleLabel label("text");
    DecorateTransformation decorateTransform;
    ReplaceTransformation replaceTransform("t", "T");

    TextTransformationDecorator decorateDecorator(label, decorateTransform);
    TextTransformationDecorator replaceDecorator(decorateDecorator, replaceTransform);

    SECTION("Add and Then Remove Replace Transformation") {
        Label* result = LabelDecoratorBase::removeDecoratorFrom(replaceDecorator, replaceDecorator);
        REQUIRE(result->getText() == "-={ text }=-");
    }

}

TEST_CASE("Decorator Removal in Empty Label", "[EmptyLabelDecoratorRemoval]") {
    SimpleLabel emptyLabel("");
    CapitalizeTransformation capitalizeTransform;

    TextTransformationDecorator decorator(emptyLabel, capitalizeTransform);

    SECTION("Removing Decorator from Empty Label") {
        Label* result = LabelDecoratorBase::removeDecoratorFrom(decorator, decorator);
        REQUIRE(result->getText().empty());
    }
}

TEST_CASE("Decorator Removal with Duplicated Decorators", "[DuplicatedDecoratorsRemoval]") {
    SimpleLabel label("data");
    CapitalizeTransformation capitalizeTransform;

    TextTransformationDecorator firstDecorator(label, capitalizeTransform);
    TextTransformationDecorator secondDecorator(firstDecorator, capitalizeTransform);

    SECTION("Remove Duplicate Decorator") {
        Label* result = LabelDecoratorBase::removeDecoratorFrom(secondDecorator, firstDecorator);
        REQUIRE(result->getText() == "Data");
    }

    SECTION("Remove Both Duplicates") {
        Label* firstRemoval = LabelDecoratorBase::removeDecoratorFrom(secondDecorator, firstDecorator);
        Label* secondRemoval = LabelDecoratorBase::removeDecoratorFrom(*firstRemoval, firstDecorator);
        REQUIRE(secondRemoval->getText() == "data");
    }
}


