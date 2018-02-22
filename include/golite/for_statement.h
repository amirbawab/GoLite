#ifndef GOLITE_STATEMENTS_FOR_H
#define GOLITE_STATEMENTS_FOR_H

#include <golite/statement.h>
#include <golite/scope.h>
#include <golite/expression.h>

namespace golite {
    class ForStatement : Statement {
    protected:
        Scope* body_;
        Expression* expression_;
    };
}

#endif
