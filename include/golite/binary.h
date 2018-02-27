#ifndef GOLITE_EXPRESSIONS_BINARY_H
#define GOLITE_EXPRESSIONS_BINARY_H

#include <golite/expression.h>

namespace golite {

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
    class Binary : public Expression {
    public:

        /**
         * Kind of binary expressions
         */
        enum KIND {
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
            OR
        };

        /**
         * Binary expression constructor
         * @param lhs
         * @param rhs
         * @param kind
         */
        Binary(Expression* lhs, Expression* rhs, KIND kind) : lhs_(lhs), rhs_(rhs), kind_(kind) {}

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
         * Get operation kind
         * @return type of the binary operation
         */
        KIND getKind() const { return kind_; }

        /**
         * @see Statement
         */
        std::string toGoLite(int indent);

        /**
         * Get line number
         * @return line number
         */
        int getLine();
    private:

        // expression + ...
        Expression* lhs_ = nullptr;

        // ... + expression
        Expression* rhs_ = nullptr;

        // Binary expression type
        KIND kind_;
    };
}

#endif
