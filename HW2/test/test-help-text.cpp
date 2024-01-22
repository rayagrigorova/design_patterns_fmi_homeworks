// #include "catch2/catch_all.hpp"
#include <catch2/catch_test_macros.hpp>

#include "Labels.h"
#include "STDINLabel.h"
#include "LabelDecorators.h"
#include "CompositeTransformation.h"
#include "Transformations.h"
#include "SimpleHelpLabel.h"

TEST_CASE("SimpleHelpLabel with SimpleLabel") {
    SimpleLabel baseLabel("Test Label");
    SimpleHelpLabel helpLabel(baseLabel, "This is a help text");

    SECTION("Check getText") {
        REQUIRE(helpLabel.getText() == "Test Label");
    }

    SECTION("Check getHelpText") {
        REQUIRE(helpLabel.getHelpText() == "This is a help text");
    }
}

TEST_CASE("SimpleHelpLabel with RichLabel") {
    RichLabel richLabel("Rich Label", "blue", "Arial", 12);
    SimpleHelpLabel helpLabel(richLabel, "Rich label help");

    SECTION("Check getText") {
        REQUIRE(helpLabel.getText() == "Rich Label");
    }

    SECTION("Check getHelpText") {
        REQUIRE(helpLabel.getHelpText() == "Rich label help");
    }
}

// TEST_CASE("SimpleHelpLabel with STDINLabel") {
//     STDINLabel stdinLabel(5);
//     SimpleHelpLabel helpLabel(stdinLabel, "Input label help");
// 
//     SECTION("Check getText") {
//         REQUIRE(helpLabel.getText() == "enter this in console");
//     }
// 
//     SECTION("Check getHelpText") {
//         REQUIRE(helpLabel.getHelpText() == "Input label help");
//     }
// }

TEST_CASE("SimpleHelpLabel with Decorated Label") {
    SimpleLabel baseLabel("decorated Label");
    CapitalizeTransformation capitalizeTransformation;
    TextTransformationDecorator decorator(baseLabel, capitalizeTransformation);
    SimpleHelpLabel helpLabel(decorator, "Decorated label help");

    SECTION("Check getText") {
        REQUIRE(helpLabel.getText() == "Decorated Label");
    }

    SECTION("Check getHelpText") {
        REQUIRE(helpLabel.getHelpText() == "Decorated label help");
    }
}
