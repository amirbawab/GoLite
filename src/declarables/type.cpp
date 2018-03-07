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
    identifier_->weedingPass(false, false);
    type_component_->weedingPass();
}

void golite::Type::symbolTablePass(SymbolTable *root) {
    if(root->getSymbol(this->identifier_->getName(), false)) {
        golite::Utils::error_message(this->identifier_->getName() + "redeclared in this block", this->getLine());
    }

    root->putSymbol(this->identifier_->getName(), this);
}

std::string golite::Type::toPrettySymbol() {
    return "type";
}