#pragma once

#include "Labels.h"

// This is the 'abstraction' base class in the bridge pattern
// The 'implementation' is 'Label'
class HelpLabel : public Label {
protected:
    Label& label;
public:
    HelpLabel(Label& label) : label(label){}
    virtual std::string getHelpText() const = 0;

    std::string getText() override {
        return label.getText();
    }
};

class SimpleHelpLabel : public HelpLabel {
    std::string helpText;

public:
    SimpleHelpLabel(Label& label, const std::string& helpText)
        : HelpLabel(label), helpText(helpText) {}

    std::string getHelpText() const override {
        return helpText;
    }

    virtual Label* clone() const override {
        return new SimpleHelpLabel(label, helpText);
    }
};