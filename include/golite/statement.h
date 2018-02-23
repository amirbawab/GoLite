#ifndef GOLITE_STATEMENTS_STATEMENT_H
#define GOLITE_STATEMENTS_STATEMENT_H

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
    protected:

        // Line number
        int line_;
    public:

        /**
         * Get line number
         * @return statement line number
         */
        int getLine() const {return line_; }
    };
}

#endif