#ifndef GOLITE_EXPRESSIONS_BINARY_H
#define GOLITE_EXPRESSIONS_BINARY_H

#include <golite/expression.h>

namespace golite {
    enum BinaryExpressionType {
        BINARY_MINUS,
        BINARY_PLUS,
        BINARY_MULTIPLY,
        BINARY_DIVIDE,
        BINARY_MODULO,
        BINARY_BIT_AND,
        BINARY_BIT_OR,
        BINARY_BIT_XOR,
        BINARY_BIT_CLEAR,
        BINARY_LEFT_SHIFT,
        BINARY_RIGHT_SHIFT,
        BINARY_IS_EQUAL,
        BINARY_IS_NOT_EQUAL,
        BINARY_LESS_THAN,
        BINARY_LESS_THAN_EQUAL,
        BINARY_GREATER_THAN,
        BINARY_GREATER_THAN_EQUAL,
        BINARY_AND,
        BINARY_OR,
        BINARY_DOT
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
