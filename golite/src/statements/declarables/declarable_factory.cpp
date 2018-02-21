#include <golite/statements/declarables/declarable_factory.h>

using namespace golite;

VariableDeclarable* DeclarableFactory::createVarDecl(std::string name, TypeDeclarable* type) {
    return new VariableDeclarable(name, type);
}