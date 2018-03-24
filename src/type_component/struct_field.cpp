#include <golite/struct_field.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/type.h>

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
    type_component_->symbolTablePass(root);
}

bool golite::StructField::isRecursive(Type *type) {
    return type_component_->isCompatible(type->toTypeComponent()) || type_component_->isRecursive(type);
}

std::string golite::StructField::toTypeScript(int indent) {
    std::stringstream ss;
    for(Identifier* identifier : identifiers_) {
        ss << golite::Utils::indent(indent) << identifier->getName()
           << " : " << type_component_->toTypeScript(indent)
           << " = " << type_component_->toTypeScriptDefaultValue();
    }
    return ss.str();
}