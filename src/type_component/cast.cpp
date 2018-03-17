#include<golite/cast.h>
#include <sstream>

std::string golite::Cast::toGoLite(int indent) {
    return type_component_->toGoLite(indent);
}

std::string golite::Cast::toGoLiteMin() {
    std::stringstream ss;
    ss << "(<expr>) -> " << type_component_->toGoLiteMin();
    return ss.str();
}

int golite::Cast::getLine() {
    return type_component_->getLine();
}

void golite::Cast::weedingPass() {
    type_component_->weedingPass();
}

void golite::Cast::symbolTablePass(SymbolTable *root) {
    return type_component_->symbolTablePass(root);
}

bool golite::Cast::isCompatible(TypeComposite *type_composite) {
    return false;
}

std::string golite::Cast::toPrettySymbol() {
    return type_component_->toPrettySymbol();
}

std::vector<golite::TypeComposite*> golite::Cast::resolveChildren() {
    return {this};
}