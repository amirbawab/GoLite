#include <golite/type_reference.h>
#include <sstream>
#include <iostream>
#include <golite/utils.h>

std::string golite::TypeReference::toGoLite(int indent) {
    std::stringstream ss;
    ss << identifier_->toGoLite(0);
    return ss.str();
}

std::string golite::TypeReference::toGoLiteMin() {
    return identifier_->toGoLite(0);
}

int golite::TypeReference::getLine() {
    return identifier_->getLine();
}

void golite::TypeReference::weedingPass() {
    if(identifier_->isBlank()) {
        golite::Utils::error_message("Type cannot be a blank identifier", identifier_->getLine());
    }
    identifier_->weedingPass();
}

void golite::TypeReference::symbolTablePass(SymbolTable *root) {
    Declarable* declarable = root->getSymbol(identifier_->getName());
    if(!declarable) {
        golite::Utils::error_message("Undefined type " + identifier_->getName(), identifier_->getLine());
    }
    if(!declarable->isTypeDeclaration()) {
        golite::Utils::error_message("Identifier " + identifier_->getName() + " is not a type declaration", identifier_->getLine());
    }
    declarable_type_ = declarable;
}

bool golite::TypeReference::isCompatible(TypeComposite *type_composite) {
    if(!type_composite->isTypeReference()) {
        return false;
    }
    TypeReference* type_reference = static_cast<TypeReference*>(type_composite);
    return declarable_type_ == type_reference->declarable_type_;
}

std::string golite::TypeReference::toPrettySymbol() {
    std::stringstream ss;
    ss << "(" << identifier_->toGoLite(0);
    if(!built_in_) {
        if(!declarable_type_ || !declarable_type_->getTypeComponent()) {
            throw std::runtime_error("Declarable or declarable type is empty. Verify symbol table pass.");
        }
        ss  << " -> " << declarable_type_->getTypeComponent()->toPrettySymbol();
    }
    ss << ")";
    return ss.str();
}

bool golite::TypeReference::resolvesTo(Declarable* declarable) {
    if(!declarable->getTypeComponent() || declarable->getTypeComponent()->getChildren().size() != 1) {
        throw std::runtime_error("Type composite cannot resolve a declarable with number of children not equal to 1");
    }
    if(isCompatible(declarable->getTypeComponent()->getChildren().front())) {
        return true;
    }
    if(built_in_) {
        return false;
    }
    return declarable_type_->getTypeComponent()->resolvesTo(declarable);
}

std::vector<golite::TypeComposite*> golite::TypeReference::resolveChildren() {
    if(built_in_) {
        return {this};
    }
    if(!declarable_type_ || !declarable_type_->getTypeComponent()) {
        throw std::runtime_error("Cannot resolve children because declarable or declarable type is empty. "
                                         "Verify symbol table pass.");
    }
    return declarable_type_->getTypeComponent()->resolveChildren();
}