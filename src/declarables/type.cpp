#include <golite/type.h>
#include <sstream>
#include <golite/utils.h>

std::string golite::Type::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "type " << identifier_->toGoLite(0) << " "
       << type_component_->toGoLite(indent) << ";";
    return ss.str();
}

int golite::Type::getLine() {
    return identifier_->getLine();
}

void golite::Type::weedingPass(bool, bool) {
    identifier_->weedingPass();
    type_component_->weedingPass();
}

void golite::Type::typeCheck() {
    // Do nothing
}

void golite::Type::symbolTablePass(SymbolTable *root) {
    if(root->hasSymbol(this->identifier_->getName(), false)) {
        golite::Utils::error_message("Type name " + identifier_->getName() + " redeclared in this block", getLine());
    }

    root->putSymbol(this->identifier_->getName(), this);
}

std::string golite::Type::toPrettySymbol() {
    return "type";
}