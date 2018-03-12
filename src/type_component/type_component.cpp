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
    return isCompatible(golite::Program::BOOL_BUILTIN_TYPE->getTypeComponent());
}

bool golite::TypeComponent::isInt() {
    return isCompatible(golite::Program::INT_BUILTIN_TYPE->getTypeComponent());
}

bool golite::TypeComponent::isFloat64() {
    return isCompatible(golite::Program::FLOAT64_BUILTIN_TYPE->getTypeComponent());
}

bool golite::TypeComponent::isRune() {
    return isCompatible(golite::Program::RUNE_BUILTIN_TYPE->getTypeComponent());
}

bool golite::TypeComponent::isString() {
    return isCompatible(golite::Program::STRING_BUILTIN_TYPE->getTypeComponent());
}

bool golite::TypeComponent::isInfer() {
    return isCompatible(golite::Program::INFER_TYPE->getTypeComponent());
}

bool golite::TypeComponent::isVoid() {
    return isCompatible(golite::Program::VOID_TYPE->getTypeComponent());
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

bool golite::TypeComponent::resolvesTo(Declarable* declarable) {
    if(children_.size() != 1 || declarable->getTypeComponent()->children_.size() != 1) {
        return false;
    }
    return children_.front()->resolvesTo(declarable);
}

std::string golite::TypeComponent::toPrettySymbol() {
    std::stringstream ss;
    if(children_.empty()) {
        throw std::runtime_error("Cannot prettify symbol an empty type component");
    }

    for(size_t i = children_.size(); i > 0; i--) {
        ss << children_[i-1]->toPrettySymbol();
    }
    return ss.str();
}

bool golite::TypeComponent::isTypeReference(std::string name) {
    if(children_.size() != 1) {
        return false;
    }
    if(!children_.front()->isTypeReference()) {
        return false;
    }
    TypeReference* type_reference = static_cast<TypeReference*>(children_.front());
    return type_reference->getIdentifier()->getName() == name;
}

bool golite::TypeComponent::resolvesToBool() {
    return resolvesTo(golite::Program::BOOL_BUILTIN_TYPE);
}

bool golite::TypeComponent::resolvesToFloat64() {
    return resolvesTo(golite::Program::FLOAT64_BUILTIN_TYPE);
}

bool golite::TypeComponent::resolvesToInt() {
    return resolvesTo(golite::Program::INT_BUILTIN_TYPE);
}

bool golite::TypeComponent::resolvesToString() {
    return resolvesTo(golite::Program::STRING_BUILTIN_TYPE);
}

bool golite::TypeComponent::resolvesToRune() {
    return resolvesTo(golite::Program::RUNE_BUILTIN_TYPE);
}

bool golite::TypeComponent::resolvesToComparable() {
    // Everything is comparable
    return true;
}

bool golite::TypeComponent::resolvesToOrdered() {
    return resolvesToInt() || resolvesToFloat64() || resolvesToRune() || resolvesToString();
}

bool golite::TypeComponent::resolvesToNumeric() {
    return resolvesToInt() || resolvesToFloat64() || resolvesToRune();
}

std::vector<golite::TypeComposite*> golite::TypeComponent::resolveChildren() {
    std::vector<golite::TypeComposite*> children;
    for(size_t i=0; i < children_.size(); i++) {
        std::vector<golite::TypeComposite*> resolved_children = children_[i]->resolveChildren();
        children.insert(children.end(), resolved_children.begin(), resolved_children.end());
    }
    return children;
}

bool golite::TypeComponent::isBaseType() {
    return isInt()
           || isFloat64()
           || isBool()
           || isString()
           || isRune();
}

bool golite::TypeComponent::resolvesToBaseType() {
    return resolvesToInt()
           || resolvesToFloat64()
           || resolvesToBool()
           || resolvesToString()
           || resolvesToRune();
}
