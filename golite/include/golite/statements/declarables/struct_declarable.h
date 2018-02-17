#ifndef GOLITE_STATEMENTS_DECLARABLES_STRUCT_H
#define GOLITE_STATEMENTS_DECLARABLES_STRUCT_H

#include <vector>
#include <golite/statements/declarables/declarable.h>
#include <golite/statements/declarables/variable_declarable.h>

namespace golite {
    class StructDeclarable : Declarable {
    protected:
        std::vector<VariableDeclarable*> variables_;
    };
}

#endif