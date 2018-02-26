#ifndef GOLITE_STATEMENTS_STATEMENT_H
#define GOLITE_STATEMENTS_STATEMENT_H

#include <string>

namespace golite {

    /**
     * Parent class for all kind of statements
     * - print
     * - println
     * - return
     * - break
     * - continue
     * - simple
     * - block
     * - for
     * - switch
     * - if
     */
    class Statement {
    public:

        /**
         * Convert to GoLite
         * @param indent
         * @return golite code
         */
        virtual std::string toGoLite(int indent) = 0;

        /**
         * Break statement overrides this function
         * @return true for break statements
         */
        virtual bool isBreak() { return false; }

        /**
         * Continue statement overrides this function
         * @return true for continue statements
         */
        virtual bool isContinue() { return false; }

        /**
         * If statement overrides this function
         * @return true for if statements
         */
        virtual bool isIf() { return false; }

        /**
         * For statement overrides this function
         * @return true for for statements
         */
        virtual bool isFor() { return false; }

        /**
         * Switch statement overrides this function
         * @return true for switch statements
         */
        virtual bool isSwitch() { return false; }

        /**
         * Block statement overrides this function
         * @return true for block statements
         */
        virtual bool isBlock() { return false; }
    };
}

#endif