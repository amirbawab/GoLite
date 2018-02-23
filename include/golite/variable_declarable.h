#ifndef GOLITE_STATEMENTS_DECLARABLES_VARIABLE_H
#define GOLITE_STATEMENTS_DECLARABLES_VARIABLE_H

#include <string>

#include <golite/declarable.h>
#include <golite/type_declarable.h>
#include <golite/expression.h>

namespace golite {
    /**
     * Variable declaration as a statement or a global declaration
     * var id ...
     */
    class VariableDeclarable : public Declarable, public Statement {
    public:
        VariableDeclarable(std::string name, TypeDeclarable* type) : Declarable(name) {
            this->type_ = type;
        }
    protected:
        // FIXME Fix type
        TypeDeclarable* type_;
        Expression* expression_;
    };
}

#endif
