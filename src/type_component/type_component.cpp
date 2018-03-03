#include <golite/type_component.h>
#include <golite/utils.h>
#include <sstream>
#include <iostream>
#include <golite/type_reference.h>

std::string golite::TypeComponent::toGoLite(int indent) {
    std::stringstream ss;
    if(children_.empty()) {
        throw std::runtime_error("Cannot prettify an empty type component");
    }

    for(size_t i = children_.size(); i > 0; i--) {
        ss << children_[i-1]->toGoLite(indent);
    }
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

void golite::TypeComponent::weedingPass() {
    for(TypeComposite* type_composite : children_) {
        type_composite->weedingPass();
    }
}

bool golite::TypeComponent::isInt() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if type component is int because list of children is empty");
    }
    return children_.size() == 1 && children_.front()->isInt();
}

bool golite::TypeComponent::isFloat64() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if type component is float64 because list of children is empty");
    }
    return children_.size() == 1 && children_.front()->isFloat64();
}

bool golite::TypeComponent::isBool() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if type component is boolean because list of children is empty");
    }
    return children_.size() == 1 && children_.front()->isBool();
}

bool golite::TypeComponent::isString() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if type component is string because list of children is empty");
    }
    return children_.size() == 1 && children_.front()->isString();
}

bool golite::TypeComponent::isRune() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if type component is rune because list of children is empty");
    }
    return children_.size() == 1 && children_.front()->isRune();
}
