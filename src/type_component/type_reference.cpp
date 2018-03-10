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
    declarable_type_ = declarable;
}

bool golite::TypeReference::isCompatible(TypeComposite *type_composite) {
    if(!type_composite->isTypeReference()) {
        return false;
    }
    TypeReference* type_reference = static_cast<TypeReference*>(type_composite);
    return declarable_type_ == type_reference->declarable_type_;
}