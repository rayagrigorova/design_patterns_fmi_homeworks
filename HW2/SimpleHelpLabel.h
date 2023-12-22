#pragma once

#include "Labels.h"

// This is the 'abstraction' base class in the bridge pattern
class HelpLabel : public Label {
protected:
    Label& label;
public:
    HelpLabel(Label& label) : label(label){}
    virtual std::string getHelpText() const = 0;
};

class SimpleHelpLabel : public HelpLabel {
    std::string helpText;

public:
    SimpleHelpLabel(Label& label, const std::string& helpText)
        : HelpLabel(label), helpText(helpText) {}

    std::string getText() override {
        return label.getText();
    }

    std::string getHelpText() const override {
        return helpText;
    }
};