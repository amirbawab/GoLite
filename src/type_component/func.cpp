#include<golite/func.h>
#include <sstream>

std::string golite::Func::toGoLite(int indent) {
    return type_component_->toGoLite(indent);
}

std::string golite::Func::toGoLiteMin() {
    std::stringstream ss;
    ss << "(";
    std::vector<FunctionParam*> params = function_->getParamsSeparated();
    for(size_t i=0; i < params.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << params[i]->getTypeComponent()->toGoLiteMin();
    }
    ss << ") -> " << type_component_->toGoLiteMin();
    return ss.str();
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
    // In golite, we don't compare function pointers
    return false;
}

std::string golite::Func::toPrettySymbol() {
    return type_component_->toPrettySymbol();
}

std::vector<golite::TypeComposite*> golite::Func::resolveChildren() {
    return {this};
}