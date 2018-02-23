#ifndef GOLITE_STATEMENTS_ASSIGNMENT_H
#define GOLITE_STATEMENTS_ASSIGNMENT_H

#include <golite/simple.h>
#include <golite/expression.h>

/**
 * Assignment expression in GoLite are not expression
 * This class represent an assignment statement
 *
 * statement: <expr> <operator> <expr>
 * operator:
 *   =
 *   +=
 *   -=
 *   *=
 *   /=
 *   %=
 *   &=
 *   |=
 *   ^=
 *   <<=
 *   >>=
 *   &^=
 */
namespace golite {
    class Assignment : public Simple {
    private:

        // expression = ...
        Expression* left_expression_;

        // ... = expression
        Expression* right_expression_;

        // Assignment kind
        golite::AssignmentStatement::KIND kind_;
    public:

        /**
         * Assignment statement kinds
         */
        enum KIND {
            EQUAL,
            PLUS_EQUAL,
            MINUS_EQUAL,
            MULTIPLY_EQUAL,
            DIVIDE_EQUAL,
            MODULO_EQUAL,
            LEFT_SHIFT_EQUAL,
            RIGHT_SHIFT_EQUAL,
            BIT_AND_EQUAL,
            BIT_OR_EQUAL,
            BIT_XOR_EQUAL,
            BIT_CLEAR_EQUAL
        };

        /**
         * Get left expression
         * @return left expression
         */
        Expression* getLeftExpression() const { return left_expression_;}

        /**
         * Get right expression
         * @return right expression
         */
        Expression* getRightExpression() const { return right_expression_; }

        /**
         * Set left expression
         * @param expression
         */
        void setLeftExpression(Expression* expression) { left_expression_ = expression; }

        /**
         * Set right expression
         * @param expression
         */
        void setRightExpression(Expression* expression) { right_expression_ = expression; }

        /**
         * Get assignment kind
         * @return assignment kind
         */
        KIND getKind() const {return kind_;}

        /**
         * Set assignment kind
         * @param kind
         */
        void setKind(KIND kind) { kind_ = kind; }
    };
}

#endif
