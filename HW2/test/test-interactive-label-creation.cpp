#include <catch2/catch_test_macros.hpp>

#include "InteractiveLabelCreation.h"
#include "Transformations.h"
#include "CompositeTransformation.h"
#include "LabelDecorators.h"

TEST_CASE("Create SimpleLabel InteractiveLabelCreation") {
    SimpleLabel label = createSimpleLabel("Simple Text");
    REQUIRE(label.getText() == "Simple Text");
}

TEST_CASE("Create Rich Label InteractiveLabelCreation") {
    RichLabel label = createRichLabel("Rich Text", "Red", "Arial", 12);
    REQUIRE(label.getText() == "Rich Text");
    REQUIRE(label.color == "Red");
    REQUIRE(label.font == "Arial");
    REQUIRE(label.fontSize == 12);
}

TEST_CASE("Add Help Text to Label InteractiveLabelCreation") {
    SimpleLabel baseLabel("Base Text");
    SimpleHelpLabel helpLabel = addHelpText(baseLabel, "Helpful information");
    REQUIRE(helpLabel.getText() == "Base Text");
    REQUIRE(helpLabel.getHelpText() == "Helpful information");
}

TEST_CASE("Add Transformation to Label InteractiveLabelCreation") {
    SimpleLabel baseLabel("transform Me");
    CapitalizeTransformation transformation;
    TextTransformationDecorator transformedLabel = addTransformation(baseLabel, transformation);
    REQUIRE(transformedLabel.getText() == "Transform Me");
}

TEST_CASE("Add Random Transformation Decorator to Label InteractiveLabelCreation") {
    SimpleLabel baseLabel("random Transform");
    std::vector<std::unique_ptr<TextTransformation>> transformations;
    transformations.push_back(std::make_unique<CapitalizeTransformation>());
    transformations.push_back(std::make_unique<CensorTransformation>("random"));

    RandomTransformationDecorator randomTransformedLabel = addRandomTransformationDecorator(baseLabel, std::move(transformations));
    std::string result = randomTransformedLabel.getText();
    REQUIRE((result == "Random Transform" || result == "****** Transform"));
}

TEST_CASE("CompositeTransformation with Multiple Transformations InteractiveLabelCreation") {
    CompositeTransformation compositeTrans;
    compositeTrans.add(std::make_unique<TrimLeftTransformation>());
    compositeTrans.add(std::make_unique<CapitalizeTransformation>());
    compositeTrans.add(std::make_unique<DecorateTransformation>());

    SECTION("Apply composite transformation sequence InteractiveLabelCreation") {
        SimpleLabel l("     some text    to be changed");
        TextTransformationDecorator res = addTransformation(l, compositeTrans);
        REQUIRE(res.getText() == "-={ Some text    to be changed }=-");
    }

    SECTION("Composite transformation maintains order of operation InteractiveLabelCreation") {
        compositeTrans.add(std::make_unique<ReplaceTransformation>("ab", "def"));
        compositeTrans.add(std::make_unique<CensorTransformation>("some"));
        SimpleLabel l("   ab  some ab   some sss ssee  ");
        TextTransformationDecorator res = addTransformation(l, compositeTrans);
        REQUIRE(res.getText() == "-={ Ab  **** def   **** sss ssee   }=-");
    }
}
