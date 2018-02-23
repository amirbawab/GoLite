#ifndef GOLITE_STATEMENTS_VARIABLE_H
#define GOLITE_STATEMENTS_VARIABLE_H

#include <string>
#include <golite/declarable.h>
#include <golite/expression.h>
#include <golite/type.h>

namespace golite {
    /**
     * Variable declaration as a statement or a global declaration
     * var id ...
     */
    class Variable : public Declarable, public Statement {
        std::vector<std::string> names_;
        TypeComponent* type_component_;
        std::vector<Expression*> expressions_;
    };
}

#endif
