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
    identifier_->symbolTablePass(root);
}

bool golite::TypeReference::isCompatible(TypeComposite *type_composite) {
    // TODO
    return true;
}