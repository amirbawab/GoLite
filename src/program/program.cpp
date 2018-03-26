#include <golite/program.h>
#include <golite/utils.h>
#include <golite/function.h>
#include <golite/variable.h>
#include <golite/declarable_factory.h>
#include <golite/ts_helper.h>

// define static types
golite::Type* golite::Program::INT_BUILTIN_TYPE = golite::DeclarableFactory::createBuiltInType("int");
golite::Type* golite::Program::FLOAT64_BUILTIN_TYPE = golite::DeclarableFactory::createBuiltInType("float64");
golite::Type* golite::Program::RUNE_BUILTIN_TYPE = golite::DeclarableFactory::createBuiltInType("rune");
golite::Type* golite::Program::BOOL_BUILTIN_TYPE = golite::DeclarableFactory::createBuiltInType("bool");
golite::Type* golite::Program::STRING_BUILTIN_TYPE = golite::DeclarableFactory::createBuiltInType("string");
golite::Type* golite::Program::VOID_TYPE = golite::DeclarableFactory::createBuiltInType("<void>");
golite::Type* golite::Program::INFER_TYPE = golite::DeclarableFactory::createBuiltInType("<infer>");
golite::Type* golite::Program::UNMAPPED_TYPE = golite::DeclarableFactory::createBuiltInType("<unmapped>");
golite::Variable* golite::Program::TRUE_VAR =
        golite::DeclarableFactory::createConstant("true", BOOL_BUILTIN_TYPE->getTypeComponent());
golite::Variable* golite::Program::FALSE_VAR =
        golite::DeclarableFactory::createConstant("false", BOOL_BUILTIN_TYPE->getTypeComponent());
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

    // append built-in decalarables
    this->root_symbol_table_->putSymbol(INT_BUILTIN_TYPE->getIdentifier()->getName(), INT_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(FLOAT64_BUILTIN_TYPE->getIdentifier()->getName(), FLOAT64_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(RUNE_BUILTIN_TYPE->getIdentifier()->getName(), RUNE_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(BOOL_BUILTIN_TYPE->getIdentifier()->getName(), BOOL_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(STRING_BUILTIN_TYPE->getIdentifier()->getName(), STRING_BUILTIN_TYPE);
    this->root_symbol_table_->putSymbol(TRUE_VAR->getIdentifiers().back()->getName(), TRUE_VAR);
    this->root_symbol_table_->putSymbol(FALSE_VAR->getIdentifiers().back()->getName(), FALSE_VAR);

    // Set true and false symbol table
    TRUE_VAR->getIdentifiers().back()->setSymbolTable(root_symbol_table_);
    FALSE_VAR->getIdentifiers().back()->setSymbolTable(root_symbol_table_);
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

    ss << golite::TSHelper::codePrint(indent);
    ss << golite::TSHelper::codePrintln(indent);
    ss << golite::TSHelper::codeConstants(indent);
    ss << golite::TSHelper::codeArrayInterface(indent);
    ss << golite::TSHelper::codeSlice(indent);

    for(Declarable* declarable : declarables_) {
        ss << declarable->toTypeScript(indent) << std::endl;
    }

    // TODO Call all init

    // Call main function
    Declarable* main_dec = program_symbol_table_->getSymbol(Program::MAIN_FUNC_NAME);
    if(main_dec) {
        Function* main_func = static_cast<Function*>(main_dec);
        ss << golite::Utils::indent(indent) << "// Call main function" << std::endl;
        ss << golite::Utils::indent(indent) << main_func->getIdentifier()->toTypeScript(0) << "();";
    }
    return ss.str();
}
