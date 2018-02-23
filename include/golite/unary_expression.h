#ifndef GOLITE_EXPRESSIONS_UNARY_H
#define GOLITE_EXPRESSIONS_UNARY_H

#include <golite/expression.h>

namespace golite {
    /**
     * All types of unary operators
     */
    enum UnaryExpressionType {
        UNARY_MINUS,
        UNARY_NOT,
        UNARY_PLUS,
        UNARY_XOR
    };

    /**
     * Class representing unary expression
     * unary_expression: <operator> <expr>
     * operator:
     *     -
     *     !
     *     +
     *     ^
     */
    class UnaryExpression : public Expression {
    public:
        UnaryExpression(Expression* operand, UnaryExpressionType type) {
            this->operand_ = operand;
            this->type_ = type;
        }

        /**
         * Get operand
         * @return operand
         */
        Expression* getOperand() const { return operand_; }

        /**
         * Get type
         * @return type
         */
        UnaryExpressionType getType() const { type_; }
    protected:
        Expression* operand_;
        UnaryExpressionType type_;
    };
}

#endif
