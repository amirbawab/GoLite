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
    };
}

#endif