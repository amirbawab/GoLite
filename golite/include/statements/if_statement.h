#ifndef GOLITE_STATEMENTS_IF_H
#define GOLITE_STATEMENTS_IF_H

#include <statements/statement.h>
#include <scope/scope.h>
#include <expressions/expression.h>

namespace Golite::Statement {
    class IfStatement : Statement {
    protected:
        Expression::Expression* expression_;
        Scope::Scope* body_;
        Scope::Scope* elsebody_;
    };
}

#endif