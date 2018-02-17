#ifndef GOLITE_EXPRESSIONS_BINARY_H
#define GOLITE_EXPRESSIONS_BINARY_H

#include <golite/expressions/expression.h>

namespace golite {
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
