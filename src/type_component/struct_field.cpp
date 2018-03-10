#include <golite/struct_field.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/variable.h>

std::string golite::StructField::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << golite::Pretty::implodeIdentifiers(identifiers_);
    ss << " " << type_component_->toGoLite(indent) << ";";
    return ss.str();
}

std::string golite::StructField::toGoLiteMin() {
    std::stringstream ss;
    ss << golite::Pretty::implodeIdentifiers(identifiers_);
    ss << " " << type_component_->toGoLiteMin() << ";";
    return ss.str();
}

void golite::StructField::weedingPass() {
    for(Identifier* identifier : identifiers_) {
        identifier->weedingPass();
    }
    type_component_->weedingPass();
}

void golite::StructField::symbolTablePass(SymbolTable *root) {
    for(Identifier* identifier : identifiers_) {
        if(!identifier->isBlank()) {
            if(root->hasSymbol(identifier->getName(), false)) {
                golite::Utils::error_message("Field name " + identifier->getName()
                                             + " redeclared in this block", identifier->getLine());
            }
            golite::Variable* variable = new golite::Variable();
            variable->setIdentifiers({identifier});
            variable->setTypeComponent(type_component_);
            root->putSymbol(identifier->getName(), variable);
        }
    }
    type_component_->symbolTablePass(root);
}