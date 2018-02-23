#include <golite/statements/declarables/declarable_factory.h>

using namespace golite;

VariableDeclarable* DeclarableFactory::createVarDecl(std::string name, TypeDeclarable* type) {
    return new VariableDeclarable(name, type);
}

TypeDeclarable* DeclarableFactory::createCustomTypeDecl(std::string name) {
    return new TypeDeclarable(name, TypeDeclarableKind::CUSTOM);
}

StructDeclarable* DeclarableFactory::createStruct(std::string name, std::vector<golite::VariableDeclarable*>* vars, golite::StructDeclarable* nested_struct) {
    return new StructDeclarable(name, vars, nested_struct);
}