#pragma once

#include "SimpleHelpLabel.h"

HelpLabel::HelpLabel(Label& label) : label(label) {

}

std::string HelpLabel::getText() {
    return label.getText();
}

SimpleHelpLabel::SimpleHelpLabel(Label& label, const std::string& helpText)
    : HelpLabel(label), helpText(helpText) {

}

std::string SimpleHelpLabel::getHelpText() const {
    return helpText;
}

Label* SimpleHelpLabel::clone() const {
    return new SimpleHelpLabel(label, helpText);
}
