#ifndef GOLITE_STATEMENTS_DECLARABLES_VARIABLE_H
#define GOLITE_STATEMENTS_DECLARABLES_VARIABLE_H

#include <statements/declarables/declarable.h>
#include <statements/declarables/type_declarable.h>

namespace Golite::Statement::Declarable {
    class VariableDeclarable : Declarable {
    protected:
        TypeDeclarable* type_;
    };
}

#endif