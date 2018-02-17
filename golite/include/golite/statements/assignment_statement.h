#ifndef GOLITE_STATEMENTS_ASSIGNMENT_H
#define GOLITE_STATEMENTS_ASSIGNMENT_H

#include <golite/statements/statement.h>
#include <golite/expressions/expression.h>
#include <golite/expressions/identifier_expression.h>

namespace golite {
    class AssignmentStatement : Statement {
    protected:
        IdentifierExpression* identifier_;
        Expression* expression_;
    };
}

#endif