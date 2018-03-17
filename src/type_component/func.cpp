#include<golite/func.h>

std::string golite::Func::toGoLite(int indent) {
    return type_component_->toGoLite(indent);
}

std::string golite::Func::toGoLiteMin() {
    return type_component_->toGoLiteMin();
}

int golite::Func::getLine() {
    return type_component_->getLine();
}

void golite::Func::weedingPass() {
    type_component_->weedingPass();
}

void golite::Func::symbolTablePass(SymbolTable *root) {
    return type_component_->symbolTablePass(root);
}

bool golite::Func::isCompatible(TypeComposite *type_composite) {
    return false;
}

std::string golite::Func::toPrettySymbol() {
    return type_component_->toPrettySymbol();
}

std::vector<golite::TypeComposite*> golite::Func::resolveChildren() {
    return {this};
}