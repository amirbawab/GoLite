#ifndef GOLITE_STATEMENTS_FOR_H
#define GOLITE_STATEMENTS_FOR_H

#include <golite/statements/statement.h>
#include <golite/scope/scope.h>
#include <golite/expressions/expression.h>

namespace golite {
    class ForStatement : Statement {
    protected:
        Scope* body_;
        Expression* expression_;
    };
}

#endif