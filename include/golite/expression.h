#ifndef GOLITE_EXPRESSIONS_EXPRESSION_H
#define GOLITE_EXPRESSIONS_EXPRESSION_H

#include <golite/simple.h>

namespace golite {
    /**
     * Parent class for all kind of expressions
     * - Primary
     * - Unary
     * - Binary
     * - Append (GoLite extra feature)
     */
    class Expression : public Simple {
    public:

        /**
         * @see Statement::isExpression()
         */
        virtual bool isExpression() { return true; }

        /**
         * Check if expression is a function call
         * @return true if it is
         */
        virtual bool isFunctionCall() { return false; }

        /**
         * Check if expression is an identifier
         * @return true if it is
         */
        virtual bool isIdentifier() { return false; }

        /**
         * Check if expression is a blank identifier
         * @return true if it is
         */
        virtual bool isBlank() { return false; }
    };
}

#endif