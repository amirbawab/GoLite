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
         * @see Expression::toTypeScriptInitializer()
         */
        virtual std::string toTypeScriptInitializer(int indent) { return std::string(); }
    };
}

#endif