#ifndef GOLITE_PRIMARY_H
#define GOLITE_PRIMARY_H

#include <vector>
#include <golite/expression.h>

namespace golite {
    class Primary : public Expression {
    public:

        /**
         * Check if primary is a selector
         * @return true if it is
         */
        virtual bool isSelector() { return false; }

        /**
         * Check if primary is a literal
         * @return true if it is
         */
        virtual bool isLiteral() { return false; }

        /**
         * Check if primary is an index
         * @return true if it is
         */
        virtual bool isIndex() { return false; }

        /**
         * Check if primary is an append
         * @return true if it is
         */
        virtual bool isAppend() { return false; }

        /**
         * Check if primary is a parenthesis
         * @return true if it is
         */
        virtual bool isParenthesis() { return false; }
    };
}

#endif