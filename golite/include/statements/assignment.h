#ifndef GOLITE_STATEMENTS_ASSIGNMENT_H
#define GOLITE_STATEMENTS_ASSIGNMENT_H

#include <statements/statement.h>
#include <expressions/expression.h>

namespace Golite::Statement {
    class Assignment : Statement {
    protected:
        // TODO: identifier
        Expression::Expression* expression_;
    };
}

#endif