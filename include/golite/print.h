#ifndef GOLITE_PRINT_H
#define GOLITE_PRINT_H

#include <golite/statement.h>
#include <golite/expression.h>
#include <vector>

namespace golite {
    class Print : public Statement {
    private:
        std::vector<golite::Expression*> expressions_;
        int line_;
    public:
        Print(int line) : line_(line) {}

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

        /**
         * @see Statement::typeCheck()
         */
        void typeCheck();
    };
}

#endif