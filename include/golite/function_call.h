#ifndef GOLITE_EXPRESSIONS_FUNCTION_CALL_H
#define GOLITE_EXPRESSIONS_FUNCTION_CALL_H

#include <vector>
#include <golite/primary.h>

namespace golite {
    class FunctionCall : public Primary {
    private:
        std::vector<Expression*> args_;
        int line_;
    public:
        FunctionCall(int line) : line_(line) {}

        /**
         * Set arguments
         * @param args
         */
        void setArgs(std::vector<Expression*> args) { args_ = args; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * Get line number
         * @return line number
         */
        int getLine() { return line_; }

        /**
         * @see Expression::isFunctionCall()
         */
        bool isFunctionCall() { return true; }

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        /**
         * @see Statement::typeCheck()
         */
        golite::TypeComponent* typeCheck();
    };
}

#endif
