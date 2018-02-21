#ifndef GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_FACTORY_H
#define GOLITE_STATEMENTS_DECALRABLES_DECLARABLE_FACTORY_H

#include <string>

#include <golite/statements/declarables/variable_declarable.h>

namespace golite {
    class DeclarableFactory {
    public:
        static VariableDeclarable* createVarDecl(std::string name, TypeDeclarable* type);
    };
}

#endif