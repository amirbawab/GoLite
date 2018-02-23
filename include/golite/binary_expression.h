#ifndef GOLITE_EXPRESSIONS_BINARY_H
#define GOLITE_EXPRESSIONS_BINARY_H

#include <golite/expression.h>

namespace golite {

    /**
     * Kind of binary expressions
     */
    // TODO Move enum inside the binary class?
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
        BINARY_OR
    };

    /**
     * Class representing a binary expression
     *
     * binary_expression: <expr> <operator> <expr>
     * operator:
     *   +
     *   -
     *   *
     *   /
     *   %
     *   &
     *   |
     *   ^
     *   &^
     *   <<
     *   >>
     *   ==
     *   !=
     *   <
     *   >
     *   <=
     *   >=
     *   &&
     *   ||
     */
    class BinaryExpression : public Expression {
    public:

        /**
         * Binary expression constructor
         * @param lhs
         * @param rhs
         * @param type
         */
        BinaryExpression(Expression* lhs, Expression* rhs, BinaryExpressionType type): Expression() {
            this->lhs_ = lhs;
            this->rhs_ = rhs;
            this->type_ = type;
        }

        /**
         * Get left operand
         * @return left operand
         */
        Expression* getLeftOperand() const {return lhs_; }

        /**
         * Get right operand
         * @return right operand
         */
        Expression* getRightOperand() const {return rhs_; }

        /**
         * Get operation type
         * @return type of the binary operation
         */
        BinaryExpressionType getType() { return type_; }

    private:

        // expression + ...
        Expression* lhs_;

        // ... + expression
        Expression* rhs_;

        // Binary expression type
        BinaryExpressionType  type_;
    };
}

#endif
