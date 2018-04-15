#include <golite/function_param.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/variable.h>
#include <iostream>

std::string golite::FunctionParam::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Pretty::implodeIdentifiers(identifiers_)
       << " " << type_component_->toGoLite(indent);
    return ss.str();
}

void golite::FunctionParam::weedingPass() {
    for(Identifier* identifier : identifiers_) {
        identifier->weedingPass();
    }
    type_component_->weedingPass();
}

void golite::FunctionParam::symbolTablePass(SymbolTable *root) {
    // Note: Type component has been checked in the function symbol table pass
    for(Identifier* identifier : identifiers_) {
        if(!identifier->isBlank()) {
            if(root->hasSymbol(identifier->getName(), false)) {
                golite::Utils::error_message("Parameter name " + identifier->getName()
                                             + " redeclared in this block", identifier->getLine());
            }
            golite::Variable* variable = new golite::Variable();
            variable->setIdentifiers({identifier});
            variable->setTypeComponent(type_component_);
            root->putSymbol(identifier->getName(), variable);
            identifier->setSymbolTable(root);
        }
    }
}

std::string golite::FunctionParam::toTypeScript(int indent) {
    std::stringstream ss;
    static int count = 1;
    for(size_t i=0; i < identifiers_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        if(!identifiers_[i]->isBlank()) {
            ss << identifiers_[i]->toTypeScript(0) << " : " << type_component_->toTypeScript(0);
        } else {
            ss << "D34D_C0D3_" << count++ << " : any";
        }
    }
    return ss.str();
}

std::string golite::FunctionParam::toTypeScriptInitializer(int indent) {
    return type_component_->toTypeScriptInitializer(indent);
}