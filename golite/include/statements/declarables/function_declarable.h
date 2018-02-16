#ifndef GOLITE_STATEMENTS_DECLARABLES_FUNCTION_H
#define GOLITE_STATEMENTS_DECLARABLES_FUNCTION_H

#include <statements/declarables/declarable.h>
#include <statements/declarables/type_declarable.h>
#include <statements/declarables/variable_declarable.h>
#include <scope/scope.h>
#include <vector>

using namespace std;

namespace Golite::Statement::Declarable {
    class FunctionDeclarable : Declarable {
    protected:
        TypeDeclarable* return_type_;
        Scope::Scope* body_;
        vector<VariableDeclarable*> params_;
    };
}

#endif