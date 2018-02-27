#ifndef GOLITE_CONTINUE_H
#define GOLITE_CONTINUE_H

#include <golite/statement.h>

namespace golite {
    class Continue : public Statement {
    private:
        int line_;
    public:
        Continue(int line) : line_(line) {}

        /**
         * Get line number
         * @return line number
         */
        int getLine() { return line_; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::Continue
         */
        bool isContinue() { return true; }
    };
}

#endif