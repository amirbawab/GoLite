#ifndef GOLITE_STATEMENTS_IF_H
#define GOLITE_STATEMENTS_IF_H

#include <golite/statements/statement.h>
#include <golite/scope/scope.h>
#include <golite/expressions/expression.h>

namespace golite {
    class IfStatement : Statement {
    protected:
        Expression* expression_;
        Scope* body_;
        Scope* else_body_;
    };
}

#endif