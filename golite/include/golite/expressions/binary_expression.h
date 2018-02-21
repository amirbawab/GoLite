#ifndef GOLITE_EXPRESSIONS_BINARY_H
#define GOLITE_EXPRESSIONS_BINARY_H

#include <golite/expressions/expression.h>

namespace golite {
    enum BinaryExpressionType {
        MINUS,
        PLUS,
        MULTIPLY,
        DIVIDE,
        MODULO,
        BIT_AND,
        BIT_OR,
        BIT_XOR,
        BIT_CLEAR,
        LEFT_SHIFT,
        RIGHT_SHIFT,
        IS_EQUAL,
        IS_NOT_EQUAL,
        LESS_THAN,
        LESS_THAN_EQUAL,
        GREATER_THAN,
        GREATER_THAN_EQUAL,
        AND,
        OR,
        DOT
    };

    class BinaryExpression : public Expression {
    public:
        BinaryExpression(Expression* lhs, Expression* rhs, BinaryExpressionType type): Expression() {
            this->lhs_ = lhs;
            this->rhs_ = rhs;
            this->type_ = type;
        }
    protected:
        Expression* lhs_;
        Expression* rhs_;
        BinaryExpressionType  type_;
    };
}

#endif
