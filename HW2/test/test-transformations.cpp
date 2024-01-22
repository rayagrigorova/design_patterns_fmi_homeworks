#include <string>
#include "catch2/catch_all.hpp"
#include "Labels.h"
#include "Transformations.h"

TEST_CASE("Test capitalize")
{
    CapitalizeTransformation ct;
    REQUIRE(ct.transform("hello I am a string") == "Hello I am a string");
    REQUIRE(ct.transform("Hello please don't change me") == "Hello please don't change me");
    REQUIRE(ct.transform("9hello I am a string") == "9hello I am a string");
    REQUIRE(ct.transform(" hello I am a string") == " hello I am a string");
}

TEST_CASE("Test trim left")
{
    TrimLeftTransformation tlt;

    REQUIRE(tlt.transform("    trim me please I have so many spaces   ") == "trim me please I have so many spaces   ");
    REQUIRE(tlt.transform("Hello please don't change me") == "Hello please don't change me");
}

TEST_CASE("CapitalizeTransformation") {
    CapitalizeTransformation transformation;
    REQUIRE(transformation.transform("hello world") == "Hello world");
    REQUIRE(transformation.transform("") == "");
}

TEST_CASE("TrimLeftTransformation") {
    TrimLeftTransformation transformation;
    REQUIRE(transformation.transform("   hello world") == "hello world");
    REQUIRE(transformation.transform("hello world") == "hello world");
}

TEST_CASE("TrimRightTransformation") {
    TrimRightTransformation transformation;
    REQUIRE(transformation.transform("hello world   ") == "hello world");
    REQUIRE(transformation.transform("hello world") == "hello world");
}

TEST_CASE("NormalizeSpaceTransformation") {
    NormalizeSpaceTransformation transformation;
    REQUIRE(transformation.transform("hello   world") == "hello world");
    REQUIRE(transformation.transform("   hello   world   ") == " hello world ");
}

TEST_CASE("DecorateTransformation") {
    DecorateTransformation transformation;
    REQUIRE(transformation.transform("hello") == "-={ hello }=-");
    REQUIRE(transformation.transform("") == "-={  }=-");
}

TEST_CASE("CensorTransformation") {
    CensorTransformation transformation("world");
    REQUIRE(transformation.transform("hello world") == "hello *****");
    REQUIRE(transformation.transform("world hello") == "***** hello");
}

TEST_CASE("ReplaceTransformation") {
    ReplaceTransformation transformation("world", "planet");
    REQUIRE(transformation.transform("hello world") == "hello planet");
    REQUIRE(transformation.transform("world hello") == "planet hello");
}

// Additional tests for equality operators
TEST_CASE("Test Equality Operators") {
    SECTION("CensorTransformation Equality") {
        CensorTransformation transformation1("world");
        CensorTransformation transformation2("world");
        CensorTransformation transformation3("hello");

        REQUIRE(transformation1.equals(transformation2));
        REQUIRE_FALSE(transformation1.equals(transformation3));
    }

    SECTION("ReplaceTransformation Equality") {
        ReplaceTransformation transformation1("world", "planet");
        ReplaceTransformation transformation2("world", "planet");
        ReplaceTransformation transformation3("hello", "planet");

        REQUIRE(transformation1.equals(transformation2));
        REQUIRE_FALSE(transformation1.equals(transformation3));
    }
}



// CapitalizeTransformation Tests
TEST_CASE("Capitalize First Letter", "[CapitalizeTransformation]") {
    CapitalizeTransformation transformation;

    SECTION("Lowercase to Uppercase") {
        REQUIRE(transformation.transform("test") == "Test");
    }

    SECTION("Uppercase Unchanged") {
        REQUIRE(transformation.transform("Test") == "Test");
    }

    SECTION("Non-letter Characters") {
        REQUIRE(transformation.transform("9test") == "9test");
    }

    SECTION("Empty String") {
        REQUIRE(transformation.transform("") == "");
    }

    SECTION("Single Character") {
        REQUIRE(transformation.transform("t") == "T");
    }
}

// TrimLeftTransformation Tests
TEST_CASE("Trim Leading Spaces", "[TrimLeftTransformation]") {
    TrimLeftTransformation transformation;

    SECTION("Spaces Before Text") {
        REQUIRE(transformation.transform("   hello") == "hello");
    }

    SECTION("No Leading Spaces") {
        REQUIRE(transformation.transform("hello") == "hello");
    }

    SECTION("All Spaces") {
        REQUIRE(transformation.transform("     ") == "");
    }

    SECTION("Empty String") {
        REQUIRE(transformation.transform("") == "");
    }

    SECTION("Spaces and Tabs Mixed") {
        REQUIRE(transformation.transform("  \t \thello") == "hello");
    }
}

// TrimRightTransformation Tests
TEST_CASE("Trim Trailing Spaces", "[TrimRightTransformation]") {
    TrimRightTransformation transformation;

    SECTION("Spaces After Text") {
        REQUIRE(transformation.transform("hello   ") == "hello");
    }

    SECTION("No Trailing Spaces") {
        REQUIRE(transformation.transform("hello") == "hello");
    }

    SECTION("All Spaces") {
        REQUIRE(transformation.transform("     ") == "");
    }

    SECTION("Empty String") {
        REQUIRE(transformation.transform("") == "");
    }

    SECTION("Spaces and Tabs Mixed") {
        REQUIRE(transformation.transform("hello  \t \t") == "hello");
    }
}

// NormalizeSpaceTransformation Tests
TEST_CASE("Normalize Consecutive Spaces", "[NormalizeSpaceTransformation]") {
    NormalizeSpaceTransformation transformation;

    SECTION("Multiple Spaces in Text") {
        REQUIRE(transformation.transform("hello   world") == "hello world");
    }

    SECTION("No Consecutive Spaces") {
        REQUIRE(transformation.transform("hello world") == "hello world");
    }

    SECTION("Only Spaces") {
        REQUIRE(transformation.transform("    ") == " ");
    }

    SECTION("Empty String") {
        REQUIRE(transformation.transform("") == "");
    }

    SECTION("Leading and Trailing Spaces") {
        REQUIRE(transformation.transform("  hello world  ") == " hello world ");
    }
}

// DecorateTransformation Tests
TEST_CASE("Decorate with Brackets", "[DecorateTransformation]") {
    DecorateTransformation transformation;

    SECTION("Normal Text") {
        REQUIRE(transformation.transform("hello") == "-={ hello }=-");
    }

    SECTION("Empty String") {
        REQUIRE(transformation.transform("") == "-={  }=-");
    }

    SECTION("Whitespace Only") {
        REQUIRE(transformation.transform("   ") == "-={     }=-");
    }

    SECTION("Numerical String") {
        REQUIRE(transformation.transform("1234") == "-={ 1234 }=-");
    }

    SECTION("Long Text") {
        std::string longText(100, 'a');
        std::string expected = "-={ " + longText + " }=-";
        REQUIRE(transformation.transform(longText) == expected);
    }
}

// CensorTransformation Tests
TEST_CASE("Censor Specific Text", "[CensorTransformation]") {
    CensorTransformation censor("secret");

    SECTION("Censor in Middle") {
        REQUIRE(censor.transform("This is a secret message") == "This is a ****** message");
    }

    SECTION("Censor at Start") {
        REQUIRE(censor.transform("secret message here") == "****** message here");
    }

    SECTION("Censor at End") {
        REQUIRE(censor.transform("Message is secret") == "Message is ******");
    }

    SECTION("Multiple Occurrences") {
        REQUIRE(censor.transform("secret message and another secret") == "****** message and another ******");
    }

    SECTION("No Censor") {
        REQUIRE(censor.transform("No secrets here") == "No ******s here");
    }

    SECTION("Case Sensitive") {
        REQUIRE(censor.transform("Secret is not secret if capitalized") == "Secret is not ****** if capitalized");
    }

    SECTION("Empty String") {
        REQUIRE(censor.transform("") == "");
    }
}

TEST_CASE("Replace Specific Text", "[ReplaceTransformation]") {
    ReplaceTransformation replace("old", "new");

    SECTION("Replace in Middle") {
        REQUIRE(replace.transform("This old car") == "This new car");
    }

    SECTION("Replace at Start") {
        REQUIRE(replace.transform("old habits die hard") == "new habits die hard");
    }

    SECTION("Replace at End") {
        REQUIRE(replace.transform("Out with the old") == "Out with the new");
    }

    SECTION("Multiple Replacements") {
        REQUIRE(replace.transform("old car, old phone") == "new car, new phone");
    }

    SECTION("No Replacement") {
        REQUIRE(replace.transform("new car, new phone") == "new car, new phone");
    }

    SECTION("Empty String") {
        REQUIRE(replace.transform("") == "");
    }

    SECTION("Case Sensitive") {
        REQUIRE(replace.transform("Old is not old if capitalized") == "Old is not new if capitalized");
    }

}

TEST_CASE("Replace text containing special chars", "[ReplaceTransformation]") {
    ReplaceTransformation replace("[", "*");
    REQUIRE(replace.transform("[[]][[][[*.*[[][[][]]]][") == "**]]**]***.***]**]*]]]]*");
}

TEST_CASE("Replace text containing special chars 2", "[ReplaceTransformation]") {
    ReplaceTransformation replace(".", "&");
    REQUIRE(replace.transform("...*wjjwk.jsdksd[.][.[][].[]*.?..).") == "&&&*wjjwk&jsdksd[&][&[][]&[]*&?&&)&");
}

TEST_CASE("Replace text containing special chars 3", "[ReplaceTransformation]") {
    ReplaceTransformation replace("?", "??");
    REQUIRE(replace.transform("?//?.[][[[][]????jdsjdsd&2441??dd923]?") == "??//??.[][[[][]????????jdsjdsd&2441????dd923]??");
}
