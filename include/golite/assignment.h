#ifndef GOLITE_STATEMENTS_ASSIGNMENT_H
#define GOLITE_STATEMENTS_ASSIGNMENT_H

#include <vector>
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
        std::vector<Expression*> left_expressions_;

        // ... = expression
        std::vector<Expression*> right_expressions_;

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
         * Get left expressions
         * @return left expressions
         */
        std::vector<Expression*> getLeftExpressions() const { return left_expressions_;}

        /**
         * Get right expressions
         * @return right expressions
         */
        std::vector<Expression*> getRightExpressions() const { return right_expressions_; }

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
