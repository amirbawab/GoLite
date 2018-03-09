#include <golite/identifier.h>
#include <golite/utils.h>
#include <golite/declarable.h>
#include <sstream>
#include <golite/type.h>

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
    if(!symbol_table_) {
        throw std::runtime_error("Symbol table is not set. Verify symbol table pass.");
    }
    Declarable* declarable = symbol_table_->getSymbol(getName());
    if(!declarable) {
        throw std::runtime_error("Identifier not found in symbol table. Verify symbol table pass.");
    }
    return declarable->getTypeComponent();
}

void golite::Identifier::symbolTablePass(SymbolTable *root) {
    if(!isBlank()) {
        // check that the identifier actually exists
        Declarable* found_symbol = root->getSymbol(this->getName());
        if(!found_symbol) {
            golite::Utils::error_message("undefined: " + this->getName(), this->getLine());
        }
    }
    symbol_table_ = root;
}

void golite::Identifier::updateTypeInSymbolTable(TypeComponent *new_type, bool search_in_parent) {
    golite::Identifier* type_id = new golite::Identifier("~infer~", -1);
    Declarable* new_declarable = new golite::Type(type_id, new_type);
    if(!symbol_table_) {
        throw std::runtime_error("Symbol table was not set. Verify symbol table pass.");
    }
    symbol_table_->updateSymbol(getName(), new_declarable, search_in_parent);
}
