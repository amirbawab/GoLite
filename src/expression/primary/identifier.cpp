#include <golite/identifier.h>
#include <golite/utils.h>
#include <golite/declarable.h>
#include <sstream>
#include <golite/type.h>
#include <iostream>
#include <golite/variable.h>

std::string golite::Identifier::BLANK = "_";

std::string golite::Identifier::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << name_;
    return ss.str();
}

bool golite::Identifier::isBlank() {
    return name_ == BLANK;
}

void golite::Identifier::weedingPass() {
    // Do nothing
}

golite::TypeComponent* golite::Identifier::typeCheck() {
    if(isBlank()) {
        throw std::runtime_error("Cannot call type check on blank identifier");
    }
    return getSymbolTableEntry()->getTypeComponent();
}

void golite::Identifier::symbolTablePass(SymbolTable *root) {
    if(isBlank()) {
        throw std::runtime_error("Cannot call symbol table check on blank identifier");
    }

    // check that the identifier actually exists
    Declarable* found_symbol = root->getSymbol(this->getName());
    if(!found_symbol) {
        golite::Utils::error_message("Undefined identifier " + this->getName(), this->getLine());
    }

    // The specific symbol table must be assigned to this identifier
    // because a future declaration of the a variable with the same name
    // and in the same scope (or sometimes close parent scope) will fetch the wrong entry
    symbol_table_ = root->getSymbolTable(getName());
}

void golite::Identifier::updateTypeInSymbolTable(TypeComponent *new_type, bool search_in_parent) {
    if(!symbol_table_) {
        throw std::runtime_error("Symbol table was not set. Verify symbol table pass.");
    }
    Declarable* entry = getSymbolTableEntry();
    if(!entry->isDecVariable()) {
        throw std::runtime_error("Cannot update symbol entry for a non-variable");
    }
    golite::Variable* variable = static_cast<Variable*>(entry);
    variable->setTypeComponent(new_type);
    symbol_table_->updateSymbol(getName(), variable, search_in_parent);
}

golite::Declarable* golite::Identifier::getSymbolTableEntry() {
    if(!symbol_table_) {
        throw std::runtime_error("Cannot get symbol table entry because symbol table was not set. "
                                         "Verify symbol table pass.");
    }

    Declarable* declarable = symbol_table_->getSymbol(getName());
    if(!declarable) {
        throw std::runtime_error("Identifier not found in symbol table while getting symbol table. "
                                         "Verify symbol table pass.");
    }
    return declarable;
}

bool golite::Identifier::isCasting() {
    return getSymbolTableEntry()->isTypeDeclaration();
}

std::string golite::Identifier::toTypeScript(int indent) {
    if(!symbol_table_) {
        throw std::runtime_error("Cannot generate code because symbol table is not set");
    }
    std::stringstream ss;
    ss << symbol_table_->getAbsoluteName() << name_;
    return ss.str();
}