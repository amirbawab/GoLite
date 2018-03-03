#include <golite/type_reference.h>
#include <sstream>
#include <iostream>
#include <golite/utils.h>

std::string golite::TypeReference::toGoLite(int indent) {
    std::stringstream ss;
    ss << identifier_->toGoLite(0);
    return ss.str();
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

bool golite::TypeReference::isInt() {
    return identifier_->getName() == "int";
}

bool golite::TypeReference::isFloat64() {
    return identifier_->getName() == "float64";
}

bool golite::TypeReference::isBool() {
    return identifier_->getName() == "bool";
}

bool golite::TypeReference::isString() {
    return identifier_->getName() == "string";
}

bool golite::TypeReference::isRune() {
    return identifier_->getName() == "rune";
}
