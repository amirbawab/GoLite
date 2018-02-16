#ifndef GOLITE_STATEMENTS_DECLARABLES_STRUCT_H
#define GOLITE_STATEMENTS_DECLARABLES_STRUCT_H

#include <vector>
#include <statements/declarables/declarable.h>
#include <statements/declarables/variable_declarable.h>

using namespace std;

namespace Golite::Statement::Declarable {
    class StructDeclarable : Declarable {
    protected:
        vector<VariableDeclarable*> variables_;
    };
}

#endif