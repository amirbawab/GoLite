#include <golite/scope/program.h>

using namespace golite;

TypeDeclarable* const Program::INT_TYPE = new TypeDeclarable("int", TypeDeclarableKind::BUILTIN);
TypeDeclarable* const Program::FLOAT_TYPE = new TypeDeclarable("float64", TypeDeclarableKind::BUILTIN);
TypeDeclarable* const Program::BOOL_TYPE = new TypeDeclarable("bool", TypeDeclarableKind::BUILTIN);
TypeDeclarable* const Program::RUNE_TYPE = new TypeDeclarable("rune", TypeDeclarableKind::BUILTIN);
TypeDeclarable* const Program::STRING_TYPE = new TypeDeclarable("string", TypeDeclarableKind::BUILTIN);

Program::Program() {
    // TODO: add the built-in types into the symbol table
}

void Program::setPackageName(string package_name) {
    this->package_name_ = package_name;
}

