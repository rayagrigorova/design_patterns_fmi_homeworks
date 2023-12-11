#include "CompositeTransformation.h"

CompositeTransformation::CompositeTransformation(const std::string& text) : text(text){

}

void CompositeTransformation::add(const Label& l) {
    children.push_back(std::make_unique<Label>(l));
}

void CompositeTransformation::add(Label&& l) {
    children.push_back(std::make_unique<Label>(std::move(l)));
}

void CompositeTransformation::remove(const Label& l) {
    auto it = std::find_if(
        children.begin(), children.end(),
        [&l](const std::unique_ptr<Label>& child) { return *child == l; });

    if (it != children.end()) {
        children.erase(it);
    }
}

std::string CompositeTransformation::getText(){
    std::string result = text;
    for (std::unique_ptr<Label>& child : children) {
        result = child->getText();
    }
    return result;
}
