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
golite::Type* golite::Program::VOID_TYPE = golite::TypeFactory::createBuiltInType("<void>");
golite::Type* golite::Program::INFER_TYPE = golite::TypeFactory::createBuiltInType("<infer>");
golite::Type* golite::Program::UNMAPPED_TYPE = golite::TypeFactory::createBuiltInType("<unmapped>");
std::string golite::Program::INIT_FUNC_NAME = "init";
std::string golite::Program::MAIN_FUNC_NAME = "main";

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
    this->root_symbol_table_ = new SymbolTable(nullptr, "golite");

    // append built-in type
    this->root_symbol_table_->putSymbol(INT_BUILTIN_TYPE->getIdentifier()->getName(), INT_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(FLOAT64_BUILTIN_TYPE->getIdentifier()->getName(), FLOAT64_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(RUNE_BUILTIN_TYPE->getIdentifier()->getName(), RUNE_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(BOOL_BUILTIN_TYPE->getIdentifier()->getName(), BOOL_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(STRING_BUILTIN_TYPE->getIdentifier()->getName(), STRING_BUILTIN_TYPE);

    // append true
    Variable* true_var = new Variable();
    Identifier* true_id = new Identifier("true", -1);
    true_var->setTypeComponent(Program::BOOL_BUILTIN_TYPE->getTypeComponent());
    true_var->setIdentifiers({true_id});
    true_var->setConstant(true);
    this->root_symbol_table_->putSymbol(true_id->getName(), true_var);

    // append false
    Variable* false_var = new Variable();
    Identifier* false_id = new Identifier("false", -1);
    false_var->setTypeComponent(Program::BOOL_BUILTIN_TYPE->getTypeComponent());
    false_var->setIdentifiers({false_id});
    false_var->setConstant(true);
    this->root_symbol_table_->putSymbol(false_id->getName(), false_var);
}

void golite::Program::symbolTablePass() {
    this->initializeSymbolTable();
    program_symbol_table_ = new SymbolTable(root_symbol_table_, "_prog");
    for(Declarable* declarable: declarables_) {
        declarable->symbolTablePass(program_symbol_table_);
    }
}

void golite::Program::typeCheck() {
    for(Declarable* declarable : declarables_) {
        declarable->typeCheck();
    }
}

std::string golite::Program::prettifySymbolTable(int indent) {
    return root_symbol_table_->toPrettySymbol(indent);
}

std::string golite::Program::toTypeScript(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "/*******************************" << std::endl
       << golite::Utils::indent(indent) << " *    GOLITE => TYPESCRIPT     *" << std::endl
       << golite::Utils::indent(indent) << " * THIS CODE IS AUTO-GENERATED *" << std::endl
       << golite::Utils::indent(indent) << " ******************************/" << std::endl
       << std::endl;

    for(Declarable* declarable : declarables_) {
        ss << declarable->toTypeScript(indent) << std::endl;
    }
    return ss.str();
}
