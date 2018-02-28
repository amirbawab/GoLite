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

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::isAssignment()
         */
        bool isAssignment() { return true; }

        /**
         * Get line
         * @return line
         */
        int getLine();

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        Assignment(std::vector<Expression*> left, std::vector<Expression*> right, KIND kind) :
                left_expressions_(left), right_expressions_(right), kind_(kind){}
    private:

        // expression = ...
        std::vector<Expression*> left_expressions_;

        // ... = expression
        std::vector<Expression*> right_expressions_;

        // Assignment kind
        golite::Assignment::KIND kind_;
    };
}

#endif
