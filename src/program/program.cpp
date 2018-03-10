#include <golite/program.h>
#include <golite/utils.h>
#include <golite/function.h>
#include <golite/variable.h>
#include <golite/type_factory.h>

// define static types
golite::Type* golite::Program::INT_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("int");
golite::Type* golite::Program::FLOAT64_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("float64");
golite::Type* golite::Program::RUNE_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("rune");
golite::Type* golite::Program::BOOL_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("bool");
golite::Type* golite::Program::STRING_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("string");
golite::Type* golite::Program::VOID_TYPE = golite::TypeFactory::createBuiltInType("");
golite::Type* golite::Program::INFER_TYPE = golite::TypeFactory::createBuiltInType("");

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
    this->root_symbol_table_->putSymbol(INT_BUILTIN_TYPE->getIdentifier()->getName(), INT_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(FLOAT64_BUILTIN_TYPE->getIdentifier()->getName(), FLOAT64_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(RUNE_BUILTIN_TYPE->getIdentifier()->getName(), RUNE_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(BOOL_BUILTIN_TYPE->getIdentifier()->getName(), BOOL_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(STRING_BUILTIN_TYPE->getIdentifier()->getName(), STRING_BUILTIN_TYPE);
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

bool golite::Program::isBuiltIn(golite::TypeComponent *type_component) {
    return type_component->isInt()
           || type_component->isFloat64()
           || type_component->isBool()
           || type_component->isString()
           || type_component->isRune();
}

bool golite::Program::resolvesToBuiltIn(golite::TypeComponent *type_component) {
    return type_component->resolvesToInt()
           || type_component->resolvesToFloat64()
           || type_component->resolvesToBool()
           || type_component->resolvesToString()
           || type_component->resolvesToRune();
}
