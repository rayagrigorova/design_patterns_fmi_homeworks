#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>

#include "CensorTransformationFactory.h"
#include "CompositeTransformation.h"
#include "InteractiveLabelCreation.h"
#include "LabelDecorators.h"
#include "Labels.h"
#include "STDINLabel.h"
#include "SimpleHelpLabel.h"
#include "Transformations.h"

// Test labels
TEST_CASE("SimpleLabel Tests") {
    SECTION("Default constructor initializes empty value") {
        SimpleLabel label;
        REQUIRE(label.getText() == "");
    }

    SECTION("Constructor with value") {
        SimpleLabel label("Test");
        REQUIRE(label.getText() == "Test");
    }

    SECTION("Clone method creates a copy") {
        SimpleLabel original("Original");
        Label* cloned = original.clone();
        REQUIRE(cloned != nullptr);
        REQUIRE(cloned->getText() == "Original");
        delete cloned;
    }
}

TEST_CASE("RichLabel Tests") {
    SECTION("Constructor initializes properties correctly") {
        RichLabel label("Test", "Red", "Arial", 12);
        REQUIRE(label.getText() == "Test");
        REQUIRE(label.color == "Red");
        REQUIRE(label.font == "Arial");
        REQUIRE(label.fontSize == 12);
    }

    SECTION("Copy constructor copies properties") {
        RichLabel original("Original", "Blue", "Helvetica", 14);
        RichLabel copy(original);
        REQUIRE(copy.getText() == "Original");
        REQUIRE(copy.color == "Blue");
        REQUIRE(copy.font == "Helvetica");
        REQUIRE(copy.fontSize == 14);
    }

    SECTION("Clone method creates a copy with same properties") {
        RichLabel original("Original", "Green", "Times", 16);
        Label* cloned = original.clone();
        REQUIRE(cloned != nullptr);

        RichLabel* clonedRichLabel = dynamic_cast<RichLabel*>(cloned);
        REQUIRE(clonedRichLabel != nullptr);
        REQUIRE(clonedRichLabel->getText() == "Original");
        REQUIRE(clonedRichLabel->color == "Green");
        REQUIRE(clonedRichLabel->font == "Times");
        REQUIRE(clonedRichLabel->fontSize == 16);

        delete cloned;
    }
}

// Test step 2

TEST_CASE("CapitalizeTransformation Tests") {
    CapitalizeTransformation capTrans;

    SECTION("Capitalizes lowercase string") {
        REQUIRE(capTrans.transform("hello") == "Hello");
    }

    SECTION("Capitalizes mixed case string") {
        REQUIRE(capTrans.transform("hElLo") == "HElLo");
    }

    SECTION("Empty string remains unchanged") {
        REQUIRE(capTrans.transform("") == "");
    }

    SECTION("Non-alphabetic characters remain unchanged") {
        REQUIRE(capTrans.transform("123") == "123");
    }

    SECTION("Clone method produces equivalent object") {
        auto cloned = capTrans.clone();
        REQUIRE(cloned->transform("world") == "World");
    }
}

TEST_CASE("TrimLeftTransformation Tests") {
    TrimLeftTransformation trimLeftTrans;

    SECTION("Removes leading spaces") {
        REQUIRE(trimLeftTrans.transform("    hello") == "hello");
    }

    SECTION("Removes leading tabs") {
        REQUIRE(trimLeftTrans.transform("\thello") == "hello");
    }

    SECTION("Does not remove trailing spaces") {
        REQUIRE(trimLeftTrans.transform("hello   ") == "hello   ");
    }

    SECTION("Empty string remains unchanged") {
        REQUIRE(trimLeftTrans.transform("") == "");
    }

    SECTION("Clone method produces equivalent object") {
        auto cloned = trimLeftTrans.clone();
        REQUIRE(cloned->transform("   world") == "world");
    }
}

TEST_CASE("TrimRightTransformation Tests") {
    TrimRightTransformation trimRightTrans;

    SECTION("Removes trailing spaces") {
        REQUIRE(trimRightTrans.transform("hello    ") == "hello");
    }

    SECTION("Removes trailing tabs") {
        REQUIRE(trimRightTrans.transform("hello\t") == "hello");
    }

    SECTION("Does not remove leading spaces") {
        REQUIRE(trimRightTrans.transform("   hello") == "   hello");
    }

    SECTION("Empty string remains unchanged") {
        REQUIRE(trimRightTrans.transform("") == "");
    }

    SECTION("Clone method produces equivalent object") {
        auto cloned = trimRightTrans.clone();
        REQUIRE(cloned->transform("world   ") == "world");
    }
}

TEST_CASE("NormalizeSpaceTransformation Tests") {
    NormalizeSpaceTransformation normSpaceTrans;

    SECTION("Replaces multiple spaces with a single space") {
        REQUIRE(normSpaceTrans.transform("hello    world") == "hello world");
    }

    SECTION("Handles leading and trailing spaces") {
        REQUIRE(normSpaceTrans.transform("  hello world  ") == " hello world ");
    }

    SECTION("Handles empty string") {
        REQUIRE(normSpaceTrans.transform("") == "");
    }

    SECTION("Clone method produces equivalent object") {
        auto cloned = normSpaceTrans.clone();
        REQUIRE(cloned->transform("hello   world") == "hello world");
    }
}

TEST_CASE("DecorateTransformation Tests") {
    DecorateTransformation decorateTrans;

    SECTION("Decorates a string") {
        REQUIRE(decorateTrans.transform("hello") == "-={ hello }=-");
    }

    SECTION("Handles empty string") {
        REQUIRE(decorateTrans.transform("") == "-={  }=-");
    }

    SECTION("Clone method produces equivalent object") {
        auto cloned = decorateTrans.clone();
        REQUIRE(cloned->transform("world") == "-={ world }=-");
    }
}

TEST_CASE("CensorTransformation Tests") {
    CensorTransformation censorTrans("test");

    SECTION("Censors specified word") {
        REQUIRE(censorTrans.transform("this is a test") == "this is a ****");
    }

    SECTION("Censors word as a part of another word") {
        REQUIRE(censorTrans.transform("testing") == "****ing");
    }

    SECTION("Clone method produces equivalent object") {
        auto cloned = censorTrans.clone();
        REQUIRE(cloned->transform("test again") == "**** again");
    }
}

TEST_CASE("ReplaceTransformation Tests") {
    ReplaceTransformation replaceTrans("test", "exam");

    SECTION("Replaces specified word") {
        REQUIRE(replaceTrans.transform("this is a test") == "this is a exam");
    }

    SECTION("Replaces word as a part of another word") {
        REQUIRE(replaceTrans.transform("testing") == "examing");
    }

    SECTION("Clone method produces equivalent object") {
        auto cloned = replaceTrans.clone();
        REQUIRE(cloned->transform("test again") == "exam again");
    }
}

TEST_CASE("Equals Method Tests") {
    CapitalizeTransformation capTrans;
    TrimLeftTransformation trimLeftTrans;

    SECTION("Different types are not equal") {
        REQUIRE_FALSE(capTrans.equals(trimLeftTrans));
    }

    SECTION("Same type objects are equal") {
        CapitalizeTransformation anotherCapTrans;
        REQUIRE(capTrans.equals(anotherCapTrans));
    }
}


// Test step 3

TEST_CASE("TextTransformationDecorator Tests") {
    SimpleLabel baseLabel("base text");
    CapitalizeTransformation transformation;

    TrimLeftTransformation trimLeft;
    TrimRightTransformation trimRight;
    NormalizeSpaceTransformation normalize;
    DecorateTransformation decorate;

    CensorTransformation censor("star this");
    CensorTransformation censor2("this");
    ReplaceTransformation replace("replace this", "new text");

    TextTransformationDecorator decorator(baseLabel, transformation);

    SECTION("getText applies transformation") {
        REQUIRE(decorator.getText() == "Base text");
    }

    SECTION("Clone method creates a copy") {
        auto cloned = decorator.clone();
        REQUIRE(dynamic_cast<TextTransformationDecorator*>(cloned)->getText() == "Base text");
        delete cloned;
    }

    SECTION("Apply trim left, trim right, normalize") {
        SimpleLabel bl("    text   replace    ");

        TextTransformationDecorator dec(bl, trimLeft);
        TextTransformationDecorator dec2(dec, trimRight);
        TextTransformationDecorator dec3(dec2, normalize);

        REQUIRE(dec3.getText() == "text replace");
    }

    SECTION("Apply censor, then replace") {
        SimpleLabel bl("replace this   this     this    replace this   ");
        TextTransformationDecorator dec(bl, censor2);
        TextTransformationDecorator dec2(dec, replace);
        REQUIRE(dec2.getText() == "replace ****   ****     ****    replace ****   ");
    }

    SECTION("Apply replace, then censor") {
        SimpleLabel bl("replace this   this     this    replace this   ");
        TextTransformationDecorator dec(bl, replace);
        TextTransformationDecorator dec2(dec, censor2);
        REQUIRE(dec2.getText() == "new text   ****     ****    new text   ");
    }

    SECTION("Apply replace, trim left, decorate") {
        SimpleLabel bl("       [*^replace^*] jjjj h    [*^replace^*]      jdjkds hj hj h j jhjjfkj sjf h[*^replace^*] jjshsj");
        ReplaceTransformation replace2("[*^replace^*]", "some other text");
        TextTransformationDecorator dec(bl, replace2);
        TextTransformationDecorator dec2(dec, trimLeft);
        TextTransformationDecorator dec3(dec2, decorate);
        REQUIRE(dec3.getText() == "-={ some other text jjjj h    some other text      jdjkds hj hj h j jhjjfkj sjf hsome other text jjshsj }=-");
    }
}

TEST_CASE("RandomTransformationDecorator Tests") {
    SimpleLabel baseLabel("base text");
    std::vector<std::unique_ptr<TextTransformation>> transformations;
    transformations.push_back(std::make_unique<CapitalizeTransformation>());
    transformations.push_back(std::make_unique<TrimLeftTransformation>());

    RandomTransformationDecorator randomDecorator(baseLabel, std::move(transformations));

    SECTION("getText applies a random transformation") {
        std::string transformedText = randomDecorator.getText();
        REQUIRE((transformedText == "Base text" || transformedText == "base text"));
    }

    SECTION("Clone method creates a copy with same transformations") {
        auto cloned = dynamic_cast<RandomTransformationDecorator*>(randomDecorator.clone());
        REQUIRE(cloned != nullptr);
        std::string clonedTransformedText = cloned->getText();
        REQUIRE((clonedTransformedText == "Base text" || clonedTransformedText == "base text"));
        delete cloned;
    }
}


// Test decorator removal 

TEST_CASE("Decorator Removal Affects Text Output", "[DecoratorRemoval]") {
    SimpleLabel baseLabel("  hello    World  ");
    CapitalizeTransformation capTransform;
    TrimLeftTransformation trimLeftTransform;
    TrimRightTransformation trimRightTransform;
    NormalizeSpaceTransformation normSpaceTransform;

    TextTransformationDecorator trimLeftDecorator(baseLabel, trimLeftTransform);
    TextTransformationDecorator capDecorator(trimLeftDecorator, capTransform);
    TextTransformationDecorator trimRightDecorator(capDecorator, trimRightTransform);
    TextTransformationDecorator normSpaceDecorator(trimRightDecorator, normSpaceTransform);

    REQUIRE(normSpaceDecorator.getText() == "Hello World");

    Label* afterTrimRightRemoval = LabelDecoratorBase::removeDecoratorFrom(normSpaceDecorator, trimRightDecorator);
    REQUIRE(afterTrimRightRemoval->getText() == "Hello World ");

    Label* afterCapRemoval = LabelDecoratorBase::removeDecoratorFrom(*afterTrimRightRemoval, capDecorator);
    REQUIRE(afterCapRemoval->getText() == "hello World ");

    Label* afterNormSpaceRemoval = LabelDecoratorBase::removeDecoratorFrom(*afterCapRemoval, normSpaceDecorator);
    REQUIRE(afterNormSpaceRemoval->getText() == "hello    World  ");

    Label* finalRemoval = LabelDecoratorBase::removeDecoratorFrom(*afterNormSpaceRemoval, trimLeftDecorator);
    REQUIRE(finalRemoval->getText() == "  hello    World  ");
}

TEST_CASE("Removing Decorators in Reverse Order", "[DecoratorRemovalReverseOrder]") {
    SimpleLabel baseLabel("example");
    DecorateTransformation decorateTransform;
    CapitalizeTransformation capitalizeTransform;

    TextTransformationDecorator capDecorator(baseLabel, capitalizeTransform);
    TextTransformationDecorator decorateDecorator(capDecorator, decorateTransform);

    REQUIRE(decorateDecorator.getText() == "-={ Example }=-");

    Label* afterCapRemoval = LabelDecoratorBase::removeDecoratorFrom(decorateDecorator, capDecorator);
    REQUIRE(afterCapRemoval->getText() == "-={ example }=-");

    Label* finalRemoval = LabelDecoratorBase::removeDecoratorFrom(*afterCapRemoval, decorateDecorator);
    REQUIRE(finalRemoval->getText() == "example");
}

TEST_CASE("Multiple Decorators of Same Type", "[MultipleSameTypeDecorators]") {
    SimpleLabel baseLabel("  data  ");
    TrimLeftTransformation trimLeftTransform;

    TextTransformationDecorator firstTrimLeftDecorator(baseLabel, trimLeftTransform);
    TextTransformationDecorator secondTrimLeftDecorator(firstTrimLeftDecorator, trimLeftTransform);

    REQUIRE(secondTrimLeftDecorator.getText() == "data  ");

    Label* afterFirstRemoval = LabelDecoratorBase::removeDecoratorFrom(secondTrimLeftDecorator, firstTrimLeftDecorator);
    REQUIRE(afterFirstRemoval->getText() == "data  ");

    Label* afterSecondRemoval = LabelDecoratorBase::removeDecoratorFrom(*afterFirstRemoval, firstTrimLeftDecorator);
    REQUIRE(afterSecondRemoval->getText() == "  data  ");
}

TEST_CASE("Multiple Decorators of Same Type But Different Actions", "[MultipleSameTypeDecorators]") {
    SimpleLabel baseLabel("  first    second    first    second    third     first     second    first  ");
    CensorTransformation ct1("first");
    CensorTransformation ct2("second");
    CensorTransformation ct3("third");

    TextTransformationDecorator firstDec(baseLabel, ct1);
    TextTransformationDecorator secondDec(firstDec, ct2);
    TextTransformationDecorator thirdDec(secondDec, ct3);

    REQUIRE(thirdDec.getText() == "  *****    ******    *****    ******    *****     *****     ******    *****  ");

    Label* afterFirstRemoval = LabelDecoratorBase::removeDecoratorFrom(thirdDec, secondDec);
    REQUIRE(afterFirstRemoval->getText() == "  *****    second    *****    second    *****     *****     second    *****  ");
    Label* afterSecondRemoval = LabelDecoratorBase::removeDecoratorFrom(thirdDec, firstDec);
    REQUIRE(afterSecondRemoval->getText() == "  first    ******    first    ******    *****     first     ******    first  ");

    afterSecondRemoval = LabelDecoratorBase::removeDecoratorFrom(thirdDec, thirdDec);
    REQUIRE(afterSecondRemoval->getText() == "  *****    ******    *****    ******    third     *****     ******    *****  ");
}

TEST_CASE("Multiple Decorators of Same Type But Different Actions 2", "[MultipleSameTypeDecorators]") {
    SimpleLabel baseLabel("  first    second    first    second    third     first     second    first  ");
    ReplaceTransformation ct1("first", "1");
    ReplaceTransformation ct2("second", "2");
    ReplaceTransformation ct3("third", "3");

    TextTransformationDecorator firstDec(baseLabel, ct1);
    TextTransformationDecorator secondDec(firstDec, ct2);
    TextTransformationDecorator Dec(secondDec, ct3);

    REQUIRE(Dec.getText() == "  1    2    1    2    3     1     2    1  ");

    Label* one = Dec.removeDecorator(Dec);
    REQUIRE(one->getText() == "  1    2    1    2    third     1     2    1  ");
    Label* two = dynamic_cast<LabelDecoratorBase*>(one)->removeDecorator(secondDec);
    REQUIRE(two->getText() == "  1    second    1    second    third     1     second    1  ");
    Label* three = dynamic_cast<LabelDecoratorBase*>(two)->removeDecorator(firstDec);
    REQUIRE(three->getText() == "  first    second    first    second    third     first     second    first  ");
}


// Composite transformation


TEST_CASE("CompositeTransformation Basic Functionality", "[CompositeTransformation]") {
    SECTION("Empty Composite Transformation") {
        CompositeTransformation composite;
        REQUIRE(composite.transform("text") == "text");
    }

    SECTION("Single Transformation") {
        std::vector<std::unique_ptr<TextTransformation>> transformations;
        transformations.push_back(std::make_unique<CapitalizeTransformation>());
        CompositeTransformation composite(std::move(transformations));
        REQUIRE(composite.transform("text") == "Text");
    }

    SECTION("Multiple Transformations") {
        std::vector<std::unique_ptr<TextTransformation>> transformations;
        transformations.push_back(std::make_unique<CapitalizeTransformation>());
        transformations.push_back(std::make_unique<DecorateTransformation>());
        CompositeTransformation composite(std::move(transformations));
        REQUIRE(composite.transform("text") == "-={ Text }=-");
    }

}

TEST_CASE("CompositeTransformation Adding and Removing Transformations", "[CompositeTransformation]") {
    std::vector<std::unique_ptr<TextTransformation>> transformations;
    transformations.push_back(std::make_unique<CapitalizeTransformation>());
    CompositeTransformation composite(std::move(transformations));
    
    SECTION("Add Transformation") {
        composite.add(std::make_unique<DecorateTransformation>());
        REQUIRE(composite.transform("text") == "-={ Text }=-");
    }

    SECTION("Remove Existing Transformation") {
        composite.remove(CapitalizeTransformation());
        REQUIRE(composite.transform("text") == "text");
    }

    SECTION("Remove Non-Existent Transformation") {
        composite.remove(DecorateTransformation());
        REQUIRE(composite.transform("text") == "Text"); 
    }

}

TEST_CASE("CompositeTransformation Cloning", "[CompositeTransformation]") {
    std::vector<std::unique_ptr<TextTransformation>> transformations;
    transformations.push_back(std::make_unique<CapitalizeTransformation>());
    transformations.push_back(std::make_unique<DecorateTransformation>());
    CompositeTransformation original(std::move(transformations));

    SECTION("Clone Composite Transformation") {
        auto cloned = original.clone();
        REQUIRE(cloned->transform("text") == "-={ Text }=-");
    }
}

TEST_CASE("CompositeTransformation Equality", "[CompositeTransformation]") {
    std::vector<std::unique_ptr<TextTransformation>> transformations1;
    transformations1.push_back(std::make_unique<CapitalizeTransformation>());

    std::vector<std::unique_ptr<TextTransformation>> transformations2;
    transformations2.push_back(std::make_unique<CapitalizeTransformation>());

    CompositeTransformation composite1(std::move(transformations1));
    CompositeTransformation composite2(std::move(transformations2));

    SECTION("Equal Composite Transformations") {
        REQUIRE(composite1.equals(composite2));
    }

    SECTION("Unequal Composite Transformations") {
        composite2.add(std::make_unique<DecorateTransformation>());
        REQUIRE_FALSE(composite1.equals(composite2));
    }
}

TEST_CASE("CompositeTransformation Complex Chains", "[CompositeTransformationComplex]") {
    CompositeTransformation complexComposite;
    complexComposite.add(std::make_unique<TrimLeftTransformation>());
    complexComposite.add(std::make_unique<CapitalizeTransformation>());
    complexComposite.add(std::make_unique<DecorateTransformation>());

    SECTION("Complex Transformation Chain") {
        REQUIRE(complexComposite.transform("  hello world") == "-={ Hello world }=-");
    }

    SECTION("Removing Middle Transformation") {
        complexComposite.remove(TrimLeftTransformation());
        REQUIRE(complexComposite.transform("  hello world") == "-={   hello world }=-");
    }

    SECTION("Adding Additional Transformation at End") {
        complexComposite.add(std::make_unique<ReplaceTransformation>("world", "Earth"));
        REQUIRE(complexComposite.transform("  hello world") == "-={ Hello Earth }=-");
    }
}

TEST_CASE("CompositeTransformation Edge Cases", "[CompositeTransformationEdge]") {
    CompositeTransformation edgeComposite;
    edgeComposite.add(std::make_unique<CapitalizeTransformation>());

    SECTION("Empty String Transformation") {
        REQUIRE(edgeComposite.transform("") == "");
    }

    SECTION("Whitespace Only String") {
        edgeComposite.add(std::make_unique<TrimLeftTransformation>());
        REQUIRE(edgeComposite.transform("   ") == "");
    }

    SECTION("Nested Composite Transformation") {
        CompositeTransformation innerComposite;
        edgeComposite.add(std::make_unique<TrimRightTransformation>());
        edgeComposite.add(std::make_unique<CompositeTransformation>(std::move(innerComposite)));
        REQUIRE(edgeComposite.transform("text  ") == "Text");
    }
}

TEST_CASE("CompositeTransformation Stress Tests", "[CompositeTransformationStress]") {
    CompositeTransformation stressComposite;
    stressComposite.add(std::make_unique<TrimRightTransformation>());
    stressComposite.add(std::make_unique<NormalizeSpaceTransformation>());
    stressComposite.add(std::make_unique<DecorateTransformation>());

    SECTION("Repeated Add and Remove") {
        for (int i = 0; i < 10; ++i) {
            stressComposite.add(std::make_unique<TrimLeftTransformation>());
            stressComposite.remove(TrimLeftTransformation());
        }
        REQUIRE(stressComposite.transform("  Text          ") == "-={  Text }=-");
    }
}

TEST_CASE("CompositeTransformation Clone Integrity", "[CompositeTransformationCloneIntegrity]") {
    CompositeTransformation originalComposite;
    originalComposite.add(std::make_unique<TrimLeftTransformation>());
    originalComposite.add(std::make_unique<CapitalizeTransformation>());

    auto clonedComposite = originalComposite.clone();
    originalComposite.remove(TrimLeftTransformation());
    originalComposite.add(std::make_unique<CensorTransformation>("text"));

    SECTION("Original Modified After Clone") {
        REQUIRE(originalComposite.transform("  text") == "  ****");
    }

    SECTION("Cloned Unaffected by Original Modification") {
        auto clonedCompositeCast = dynamic_cast<CompositeTransformation*>(clonedComposite.get());
        REQUIRE(clonedCompositeCast->transform("  text") == "Text");
    }
}


// STDIN label

TEST_CASE("STDINLabel Initial Text Input", "[ManualTest][STDINLabel]") {
    std::cout << "Manual Test: Initial Text Input\n";
    STDINLabel label(3);

    std::cout << "Action: Enter the text 'Initial Test' when prompted.\n";
    std::cout << "Expected Result: The first call to getText() should return 'Initial Test'.\n";

    // Perform the action manually
    std::string result = label.getText();
    std::cout << "Result: " << result << "\n\n";
    REQUIRE(result == "Initial Test");
}

TEST_CASE("STDINLabel Text Retrieval Without Timeout Expiration", "[ManualTest][STDINLabel]") {
    std::cout << "Manual Test: Text Retrieval Without Timeout Expiration\n";
    STDINLabel label(3);

    std::cout << "Action: Enter the text 'No Timeout Test'.\n";
    std::cout << "Expected Result: Subsequent calls to getText() should return 'No Timeout Test' without prompting for new input.\n";

    label.getText(); // Enter the text manually

    for (int i = 0; i < 2; ++i) { // Less than timeout
        std::string result = label.getText();
        std::cout << "Call " << i + 1 << " Result: " << result << "\n";
        REQUIRE(result == "No Timeout Test");
    }
    std::cout << "\n";
}

TEST_CASE("STDINLabel Text Change After Timeout", "[ManualTest][STDINLabel]") {
    std::cout << "Manual Test: Text Change After Timeout\n";
    STDINLabel label(2);

    std::cout << "Action: Enter the text 'Timeout Test', then call getText() three times.\n";
    std::cout << "Expected Result: On the third call, you should be prompted to enter new text.\n";

    label.getText(); // Enter 'Timeout Test'
    label.getText(); // Second call, no prompt

    // Enter 'y' to confirm the input of new text 

    std::cout << "On the third call, enter 'New Text' when prompted.\n";
    std::string result = label.getText(); // Enter 'New Text'
    std::cout << "Result: " << result << "\n\n";
    REQUIRE(result == "New Text");
}

TEST_CASE("STDINLabel Text Retention After Declining to Change", "[ManualTest][STDINLabel]") {
    std::cout << "Manual Test: Text Retention After Declining to Change\n";
    STDINLabel label(2);

    std::cout << "Action: Enter the text 'Decline Change Test', then call getText() three times.\n";
    std::cout << "Expected Result: On the third call, you should be prompted to change the text. Enter 'n'.\n";

    label.getText(); // Enter 'Decline Change Test'
    label.getText(); // Second call, no prompt

    std::cout << "On the third call, decline to change the text.\n";
    std::string result = label.getText(); // Enter 'n'
    std::cout << "Result: " << result << "\n\n";
    REQUIRE(result == "Decline Change Test");
}

// Help label 

TEST_CASE("SimpleHelpLabel Basic Functionality") {
    SimpleLabel baseLabel("Base Label Text");
    SimpleHelpLabel helpLabel(baseLabel, "This is help text");

    SECTION("Help text is correctly returned") {
        REQUIRE(helpLabel.getHelpText() == "This is help text");
    }

    SECTION("Base label text is correctly returned") {
        REQUIRE(helpLabel.getText() == "Base Label Text");
    }
}

TEST_CASE("SimpleHelpLabel Clone Functionality") {
    SimpleLabel baseLabel("Clonable Base Label");
    SimpleHelpLabel helpLabel(baseLabel, "Help text for clone");

    SECTION("Cloning maintains help text") {
        Label* cloned = helpLabel.clone();
        REQUIRE(dynamic_cast<SimpleHelpLabel*>(cloned)->getHelpText() == "Help text for clone");
        delete cloned;
    }
}

TEST_CASE("SimpleHelpLabel with Different Base Labels") {
    SimpleLabel simpleLabel("Simple Label Text");
    RichLabel richLabel("Rich Label Text", "Red", "Arial", 12);

    SimpleHelpLabel simpleHelpLabel(simpleLabel, "Simple help text");
    SimpleHelpLabel richHelpLabel(richLabel, "Rich label help text");

    SECTION("HelpLabel works with SimpleLabel") {
        REQUIRE(simpleHelpLabel.getText() == "Simple Label Text");
        REQUIRE(simpleHelpLabel.getHelpText() == "Simple help text");
    }

    SECTION("HelpLabel works with RichLabel") {
        REQUIRE(richHelpLabel.getText() == "Rich Label Text");
        REQUIRE(richHelpLabel.getHelpText() == "Rich label help text");
    }
}

TEST_CASE("HelpLabel with Custom Behavior") {
    SimpleLabel customLabel("Custom Label Text");
    class CustomHelpLabel : public HelpLabel {
        std::string customHelpText;
    public:
        CustomHelpLabel(Label& label, const std::string& helpText)
            : HelpLabel(label), customHelpText(helpText + " (customized)") {}

        std::string getHelpText() const override {
            return customHelpText;
        }

        Label* clone() const override {
            return new CustomHelpLabel(label, customHelpText);
        }
    };

    CustomHelpLabel customHelpLabel(customLabel, "Help for custom label");

    SECTION("Custom help label provides customized help text") {
        REQUIRE(customHelpLabel.getHelpText() == "Help for custom label (customized)");
    }
}

TEST_CASE("HelpLabel with Empty Base Label") {
    SimpleLabel emptyBaseLabel("");
    SimpleHelpLabel helpLabel(emptyBaseLabel, "Help text for an empty label");

    SECTION("Getting text from an empty base label") {
        REQUIRE(helpLabel.getText() == "");
    }

    SECTION("Getting help text for an empty base label") {
        REQUIRE(helpLabel.getHelpText() == "Help text for an empty label");
    }
}

TEST_CASE("HelpLabel Integration with Decorators") {
    SimpleLabel baseLabel("decorated Label");
    CapitalizeTransformation capitalizeTransform;
    TextTransformationDecorator decorator(baseLabel, capitalizeTransform);
    SimpleHelpLabel helpLabel(decorator, "Help text for a decorated label");

    SECTION("HelpLabel with a decorated base label") {
        REQUIRE(helpLabel.getText() == "Decorated Label");
        REQUIRE(helpLabel.getHelpText() == "Help text for a decorated label");
    }
}

 
// Dependency injection 

TEST_CASE("Create Simple Label") {
    SimpleLabel label = createSimpleLabel("Simple Text");
    REQUIRE(label.getText() == "Simple Text");
}

TEST_CASE("Create Rich Label") {
    RichLabel label = createRichLabel("Rich Text", "Red", "Arial", 12);
    REQUIRE(label.getText() == "Rich Text");
    REQUIRE(label.color == "Red");
    REQUIRE(label.font == "Arial");
    REQUIRE(label.fontSize == 12);
}

 TEST_CASE("Create STDIN Label") {
     STDINLabel label = createSTDINLabel(3);
     REQUIRE(label.getText() == "User Input Text");
 }

TEST_CASE("Add Help Text to Label") {
    SimpleLabel baseLabel = createSimpleLabel("Base Text");
    SimpleHelpLabel helpLabel = addHelpText(baseLabel, "Helpful information");
    REQUIRE(helpLabel.getText() == "Base Text");
    REQUIRE(helpLabel.getHelpText() == "Helpful information");
}

TEST_CASE("Add Transformation to Label") {
    SimpleLabel* baseLabel = new SimpleLabel("transform Me");
    CapitalizeTransformation transformation;
    TextTransformationDecorator transformedLabel = addTransformation(*baseLabel, transformation);
    REQUIRE(transformedLabel.getText() == "Transform Me");
    delete baseLabel;
}

TEST_CASE("Add Random Transformation Decorator to Label") {
    SimpleLabel* baseLabel = new SimpleLabel("    random Transform");
    std::vector<std::unique_ptr<TextTransformation>> transformations;
    transformations.push_back(std::make_unique<CensorTransformation>("random"));
    transformations.push_back(std::make_unique<TrimLeftTransformation>());

    RandomTransformationDecorator randomTransformedLabel = addRandomTransformationDecorator(*baseLabel, std::move(transformations));
    std::string res = randomTransformedLabel.getText();
    REQUIRE((res == "random Transform" || res == "    ****** Transform"));
    delete baseLabel;
}

TEST_CASE("Create Label with Multiple Decorators and Help Text") {
    SimpleLabel s = createSimpleLabel("   this   is a simple label ");
    TextTransformationDecorator middleAns = addTransformation(s, TrimLeftTransformation());
    TextTransformationDecorator t = addTransformation(middleAns, CapitalizeTransformation());
    SimpleHelpLabel help = addHelpText(t, "This is some help text for the simple label");
    REQUIRE(help.getText() == "This   is a simple label ");
    REQUIRE(help.getHelpText() == "This is some help text for the simple label");
}


TEST_CASE("Create Label With Composite Transformation and Random Transformation") {
    CompositeTransformation c;
    c.add(std::make_unique<ReplaceTransformation>("text", "apple"));
    c.add(std::make_unique<CensorTransformation>("y"));
    c.add(std::make_unique<TrimLeftTransformation>());
    c.add(std::make_unique<CapitalizeTransformation>());
    c.add(std::make_unique<NormalizeSpaceTransformation>());

    std::vector<std::unique_ptr<TextTransformation>> transformations;
    transformations.push_back(std::make_unique<DecorateTransformation>());
    transformations.push_back(std::make_unique<ReplaceTransformation>("game", "tree"));

    SimpleLabel s = createSimpleLabel("  text   text y    hhshh texty text game y game ");
    TextTransformationDecorator t = addTransformation(s, c);
    RandomTransformationDecorator rtd = addRandomTransformationDecorator(t, std::move(transformations));
    REQUIRE((rtd.getText() == "-={ Apple apple * hhshh apple* apple game * game  }=-" ||
            rtd.getText() == "Apple apple * hhshh apple* apple tree * tree "));
}


// Step 9 - Flyweight 

TEST_CASE("CensorTransformationFactory Flyweight Reuse") {
    CensorTransformationFactory factory;

    const CensorTransformation& trans1 = factory.getFlyweight("test");
    const CensorTransformation& trans2 = factory.getFlyweight("test");

    SECTION("Same instance is reused for short words") {
        REQUIRE(&trans1 == &trans2);
    }
}

TEST_CASE("CensorTransformation Correct Behavior") {
    CensorTransformationFactory factory;

    const CensorTransformation& shortWordTrans = factory.getFlyweight("test");
    const CensorTransformation& longWordTrans = factory.getFlyweight("testing");

    SECTION("Correct censoring for short words") {
        REQUIRE(shortWordTrans.transform("This is a test sentence.") == "This is a **** sentence.");
    }

    SECTION("Correct censoring for long words") {
        REQUIRE(longWordTrans.transform("testing this sentence.") == "******* this sentence.");
    }
}
