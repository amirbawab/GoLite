#ifndef GOLITE_EXPRESSIONS_UNARY_H
#define GOLITE_EXPRESSIONS_UNARY_H

#include <golite/expressions/expression.h>

namespace golite {
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