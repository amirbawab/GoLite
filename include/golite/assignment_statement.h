#ifndef GOLITE_STATEMENTS_ASSIGNMENT_H
#define GOLITE_STATEMENTS_ASSIGNMENT_H

#include <golite/statement.h>
#include <golite/expression.h>
#include <golite/identifier_expression.h>

namespace golite {
    class AssignmentStatement : Statement {
    protected:
        IdentifierExpression* identifier_;
        Expression* expression_;
    };
}

#endif
