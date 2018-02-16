#ifndef GOLITE_EXPRESSIONS_BINARY_H
#define GOLITE_EXPRESSIONS_BINARY_H

#include <expressions/expression.h>

namespace Golite::Expression {
    enum BinaryExpressionType {
        MINUS,
        PLUS,
        MULTIPLY // TODO: finish
    };

    class BinaryExpression : Expression {
    protected:
        Expression* lhs_;
        Expression* rhs_;
        BinaryExpressionType  type_;
    };
}

#endif
