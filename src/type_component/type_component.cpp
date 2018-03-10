#include <golite/type_component.h>
#include <golite/utils.h>
#include <sstream>
#include <iostream>
#include <golite/type_reference.h>
#include <golite/program.h>

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

std::string golite::TypeComponent::toGoLiteMin() {
    std::stringstream ss;
    if(children_.empty()) {
        throw std::runtime_error("Cannot min prettify an empty type component");
    }

    for(size_t i = children_.size(); i > 0; i--) {
        ss << children_[i-1]->toGoLiteMin();
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

bool golite::TypeComponent::isCompatible(TypeComponent *type_component) {

    // If the number of composite types is different they they are not compatible
    if(children_.size() != type_component->children_.size()) {
        return false;
    }

    for(size_t i=0; i < children_.size(); i++) {
        if(!children_[i]->isCompatible(type_component->children_[i])) {
            return false;
        }
    }
    return true;
}

void golite::TypeComponent::symbolTablePass(SymbolTable *root) {
    for(TypeComposite* child : children_) {
        child->symbolTablePass(root);
    }
}

bool golite::TypeComponent::isBool() {
    return this == golite::Program::BOOL_BUILTIN_TYPE->getTypeComponent();
}

bool golite::TypeComponent::isInt() {
    return this == golite::Program::INT_BUILTIN_TYPE->getTypeComponent();
}

bool golite::TypeComponent::isFloat64() {
    return this == golite::Program::FLOAT64_BUILTIN_TYPE->getTypeComponent();
}

bool golite::TypeComponent::isRune() {
    return this == golite::Program::RUNE_BUILTIN_TYPE->getTypeComponent();
}

bool golite::TypeComponent::isString() {
    return this == golite::Program::STRING_BUILTIN_TYPE->getTypeComponent();
}

bool golite::TypeComponent::isInfer() {
    return this == golite::Program::INFER_TYPE->getTypeComponent();
}

bool golite::TypeComponent::isVoid() {
    return this == golite::Program::VOID_TYPE->getTypeComponent();
}

bool golite::TypeComponent::isComparable() {
    // Everything is comparable
    return true;
}

bool golite::TypeComponent::isOrdered() {
    return isInt() || isFloat64() || isRune() || isString();
}

bool golite::TypeComponent::isNumeric() {
    return isInt() || isFloat64() || isRune();
}

std::string golite::TypeComponent::toPrettySymbol() {
    return "FIXME";
}