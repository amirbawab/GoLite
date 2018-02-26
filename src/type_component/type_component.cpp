#include <golite/type_component.h>
#include <golite/utils.h>
#include <sstream>
#include <iostream>

std::string golite::TypeComponent::toGoLite(int indent) {
    std::stringstream ss;
    for(size_t i = children_.size()-1; i > 0; i--) {
        ss << children_[i]->toGoLite(indent);
    }
    ss << children_.front()->toGoLite(indent);
    return ss.str();
}

void golite::TypeComponent::addChild(golite::TypeComponent *type_component) {
    children_.push_back(type_component);
}