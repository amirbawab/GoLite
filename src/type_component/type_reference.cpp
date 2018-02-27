#include <golite/type_reference.h>
#include <sstream>
#include <iostream>

std::string golite::TypeReference::toGoLite(int indent) {
    std::stringstream ss;
    ss << identifier_->toGoLite(0);
    return ss.str();
}

int golite::TypeReference::getLine() {
    return identifier_->getLine();
}