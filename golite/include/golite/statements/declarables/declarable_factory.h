#ifndef GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_FACTORY_H
#define GOLITE_STATEMENTS_DECALRABLES_DECLARABLE_FACTORY_H

#include <string>

#include <golite/statements/declarables/variable_declarable.h>
#include <golite/statements/declarables/type_declarable.h>
#include <golite/statements/declarables/struct_declarable.h>

namespace golite {
    class DeclarableFactory {
    public:
        static VariableDeclarable* createVarDecl(std::string name, TypeDeclarable* type);
        static TypeDeclarable* createCustomTypeDecl(std::string name);
        static StructDeclarable* createStruct(std::string name, std::vector<golite::VariableDeclarable*>* vars, golite::StructDeclarable* nested_struct = nullptr);
    };
}

#endif