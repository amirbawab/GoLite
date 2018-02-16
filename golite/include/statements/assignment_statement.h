#ifndef GOLITE_STATEMENTS_ASSIGNMENT_H
#define GOLITE_STATEMENTS_ASSIGNMENT_H

#include <statements/statement.h>
#include <expressions/expression.h>
#include <expressions/identifier_expression.h>

namespace Golite::Statement {
    class AssignmentStatement : Statement {
    protected:
        Expression::IdentifierExpression* identifier_;
        Expression::Expression* expression_;
    };
}

#endif