#ifndef GOLITE_STATEMENTS_DECLARABLES_FUNCTION_H
#define GOLITE_STATEMENTS_DECLARABLES_FUNCTION_H

#include <golite/statements/declarables/declarable.h>
#include <golite/statements/declarables/type_declarable.h>
#include <golite/statements/declarables/variable_declarable.h>
#include <golite/scope/scope.h>
#include <vector>

namespace golite {
    class FunctionDeclarable : Declarable {
    protected:
        TypeDeclarable* return_type_;
        Scope* body_;
        std::vector<VariableDeclarable*> params_;
    };
}

#endif