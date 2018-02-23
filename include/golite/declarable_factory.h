#ifndef GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_FACTORY_H
#define GOLITE_STATEMENTS_DECALRABLES_DECLARABLE_FACTORY_H

#include <string>

#include <golite/variable.h>
#include <golite/type.h>
#include <golite/struct.h>

namespace golite {
    class DeclarableFactory {
    public:
        // FIXME change parameters
        static VariableDeclarable* createVarDecl(std::string name, TypeDeclarable* type);
        static TypeDeclarable* createCustomTypeDecl(std::string name);
        static StructDeclarable* createStruct(std::string name, std::vector<golite::VariableDeclarable*>* vars, golite::StructDeclarable* nested_struct = nullptr);
    };
}

#endif
