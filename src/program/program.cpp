#include <golite/program.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/function.h>
#include <golite/variable.h>
#include <golite/type_factory.h>

// define static types
const golite::Type golite::Program::INT_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("int");
const golite::Type golite::Program::FLOAT64_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("float64");
const golite::Type golite::Program::RUNE_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("rune");
const golite::Type golite::Program::BOOL_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("bool");
const golite::Type golite::Program::STRING_BUILTIN_TYPE = golite::TypeFactory::createBuiltInType("string");

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

void golite::Program::symbolTablePass() {
    this->root_symbol_table_ = new SymbolTable(); // create new symtable
    for(Declarable* declarable: declarables_) {
        //declarable->symbolTablePass(this->root_symbol_table_);
    }
}
