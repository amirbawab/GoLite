#ifndef GOLITE_RETURN_H
#define GOLITE_RETURN_H

#include <golite/statement.h>
#include <golite/expression.h>

namespace golite {
    class Return : public Statement {
    private:
        Expression* expression_ = nullptr;
        int line_;
    public:
        Return(int line) : line_(line) {}

        /**
         * @see Statement::getLine()
         */
        int getLine() { return line_; }

        /**
         * Set expression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression;}

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

        /*
         * @see Statement::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * @see Statement::hasReturn()
         */
        bool hasReturn(Declarable* function);

        /**
         * @see Statement::isTerminating()
         */
        bool isTerminating();
    };
}

#endif