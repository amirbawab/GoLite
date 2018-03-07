#include <golite/program.h>
#include <golite/utils.h>
#include <iostream>
#include <golite/function.h>
#include <golite/variable.h>
#include <golite/type_factory.h>

// define static types
golite::Type golite::Program::INT_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("int");
golite::Type golite::Program::FLOAT64_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("float64");
golite::Type golite::Program::RUNE_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("rune");
golite::Type golite::Program::BOOL_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("bool");
golite::Type golite::Program::STRING_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("string");

std::string golite::Program::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent)<< "package " << package_name_->toGoLite(0) << ";" << std::endl;
    for(Declarable* declarable : declarables_) {
        ss << std::endl << declarable->toGoLite(indent);
    }
    return ss.str();
}

void golite::Program::weedingPass() {
    if(package_name_->isBlank()) {
        golite::Utils::error_message("Package name cannot be a blank identifier", package_name_->getLine());
    }

    for(Declarable* declarable : declarables_) {
        declarable->weedingPass(true, true);
    }
}

void golite::Program::initializeSymbolTable() {
    this->root_symbol_table_ = new SymbolTable();

    // append built-in type
    this->root_symbol_table_->putSymbol("int", &golite::Program::INT_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol("float64", &golite::Program::FLOAT64_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol("rune", &golite::Program::RUNE_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol("bool", &golite::Program::BOOL_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol("string", &golite::Program::STRING_BUILTIN_TYPE);

}

void golite::Program::symbolTablePass() {
    this->initializeSymbolTable();
    for(Declarable* declarable: declarables_) {
        declarable->symbolTablePass(this->root_symbol_table_);
    }

    std::cout << this->root_symbol_table_->prettyPrint(0) << std::endl;
}
