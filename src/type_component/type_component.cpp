#include <golite/type_component.h>
#include <golite/utils.h>
#include <sstream>
#include <iostream>

std::string golite::TypeComponent::toGoLite(int indent) {
    std::stringstream ss;
    if(children_.empty()) {
        throw std::runtime_error("Cannot prettify an empty type component");
    }

    for(size_t i = children_.size()-1; i > 0; i--) {
        ss << children_[i]->toGoLite(indent);
    }
    ss << children_.front()->toGoLite(indent);
    return ss.str();
}

void golite::TypeComponent::addChild(golite::TypeComposite *type_composite) {
    children_.push_back(type_composite);
}

int golite::TypeComponent::getLine() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot get line of an empty type component");
    }
    return children_.front()->getLine();
}