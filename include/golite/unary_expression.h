#ifndef GOLITE_EXPRESSIONS_UNARY_H
#define GOLITE_EXPRESSIONS_UNARY_H

#include <golite/expression.h>

namespace golite {
    enum UnaryExpressionType {
        UNARY_MINUS,
        UNARY_NOT,
        UNARY_PLUS,
        UNARY_XOR
    };

    class UnaryExpression : public Expression {
    public:
        UnaryExpression(Expression* operand, UnaryExpressionType type) {
            this->operand_ = operand;
            this->type_ = type;
        }
    protected:
        Expression* operand_;
        UnaryExpressionType type_;
    };
}

#endif
