#ifndef GOLITE_STATEMENTS_FOR_H
#define GOLITE_STATEMENTS_FOR_H

#include <statements/statement.h>
#include <scope/scope.h>
#include <expressions/expression.h>

namespace Golite::Statement {
    class ForStatement : Statement {
    protected:
        Scope::Scope* body_;
        Expression::Expression* expression_;
    };
}

#endif