#ifndef GOLITE_EXPRESSIONS_UNARY_H
#define GOLITE_EXPRESSIONS_UNARY_H

#include <expressions/expression.h>

namespace Golite::Expression {
    enum UnaryExpressionType {
        MINUS,
        NOT
    };

    class UnaryExpression : Expression {
    protected:
        Expression* operand_;
        UnaryExpressionType type_;
    };
}

#endif