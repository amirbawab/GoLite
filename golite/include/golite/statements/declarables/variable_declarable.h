#ifndef GOLITE_STATEMENTS_DECLARABLES_VARIABLE_H
#define GOLITE_STATEMENTS_DECLARABLES_VARIABLE_H

#include <golite/statements/declarables/declarable.h>
#include <golite/statements/declarables/type_declarable.h>

namespace golite {
    class VariableDeclarable : Declarable {
    protected:
        TypeDeclarable* type_;
    };
}

#endif