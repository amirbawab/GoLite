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

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool, bool);

        /**
         * @see Statement::typeCheck()
         */
        void typeCheck();

        /*
         * @see Statement::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * @see Statement::toTypeScript()
         */
        std::string toTypeScript(int indent);
    };
}

#endif