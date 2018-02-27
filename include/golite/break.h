#ifndef GOLITE_BREAK_H
#define GOLITE_BREAK_H

#include <golite/statement.h>

namespace golite {
    class Break : public Statement {
    private:
        int line_;
    public:
        Break(int line) : line_(line) {}

        /**
         * Get line number
         * @return line number
         */
        int getLine() const { return line_; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::isBreak()
         */
        bool isBreak() { return true; }
    };
}

#endif