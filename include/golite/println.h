#ifndef GOLITE_PRINTLN_H
#define GOLITE_PRINTLN_H

#include <vector>
#include <golite/expression.h>

namespace golite {
    class Println : public Statement {
    private:
        std::vector<golite::Expression*> expressions_;
        int line_;
    public:
        Println(int line) : line_(line) {}

        /**
         * @see Statement::getLine()
         */
        int getLine() { return line_; }

        /**
         * Set expressions
         * @param expressions
         */
        void setExpressions(std::vector<golite::Expression*> expressions) { expressions_ = expressions; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);
    };
}

#endif