#include <golite/program.h>
#include <golite/utils.h>
#include <golite/function.h>
#include <golite/variable.h>
#include <golite/type_factory.h>

// define static types
golite::Type golite::Program::INT_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("int");
golite::Type golite::Program::FLOAT64_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("float64");
golite::Type golite::Program::RUNE_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("rune");
golite::Type golite::Program::BOOL_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("bool");
golite::Type golite::Program::STRING_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("string");
golite::Type golite::Program::VOID_TYPE = golite::TypeFactory::createBuiltInType("void");

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
    this->root_symbol_table_->putSymbol(golite::Program::INT_BUILTIN_TYPE.getIdentifier()->getName(),
                                        &golite::Program::INT_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(golite::Program::FLOAT64_BUILTIN_TYPE.getIdentifier()->getName(),
                                        &golite::Program::FLOAT64_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(golite::Program::RUNE_BUILTIN_TYPE.getIdentifier()->getName(),
                                        &golite::Program::RUNE_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(golite::Program::BOOL_BUILTIN_TYPE.getIdentifier()->getName(),
                                        &golite::Program::BOOL_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(golite::Program::STRING_BUILTIN_TYPE.getIdentifier()->getName(),
                                        &golite::Program::STRING_BUILTIN_TYPE);

}

void golite::Program::symbolTablePass() {
    this->initializeSymbolTable();
    SymbolTable* program_symbol_table = new SymbolTable();
    root_symbol_table_->addChild(program_symbol_table);
    for(Declarable* declarable: declarables_) {
        declarable->symbolTablePass(program_symbol_table);
    }
}

void golite::Program::typeCheck() {
    for(Declarable* declarable : declarables_) {
        declarable->typeCheck();
    }
}

std::string golite::Program::prettifySymbolTable(int indent) {
    return root_symbol_table_->prettyPrint(indent);
}