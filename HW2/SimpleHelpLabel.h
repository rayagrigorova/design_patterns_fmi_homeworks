#pragma once

#include "Labels.h"

// This is the 'abstraction' base class in the bridge pattern
// The 'implementation' is 'Label'
class HelpLabel : public Label {
protected:
    Label& label;
public:
    HelpLabel(Label& label);
    virtual std::string getHelpText() const = 0;
    std::string getText() override;
};

class SimpleHelpLabel : public HelpLabel {
    std::string helpText;

public:
    SimpleHelpLabel(Label& label, const std::string& helpText);
    std::string getHelpText() const override;
    virtual Label* clone() const override;
};