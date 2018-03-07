#ifndef GOLITE_SWITCH_H
#define GOLITE_SWITCH_H

#include <vector>
#include <golite/expression.h>
#include <golite/switch_case.h>
#include <golite/simple.h>

namespace golite {
    class Switch : public Statement {
    private:
        Simple* simple_ = nullptr;
        Expression* expression_ = nullptr;
        std::vector<SwitchCase*> cases_;
        int line_;

    public:
        Switch(int line) : line_(line) {}

        /**
         * @see Statement::getLine()
         */
        int getLine() { return line_; }

        /**
         * Set simple
         * @param simple
         */
        void setSimple(Simple* simple) { simple_ = simple; }

        /**
         * Set epression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression;}

        /**
         * Set cases
         * @param cases
         */
        void setCases(std::vector<SwitchCase*> cases) { cases_ = cases; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::isSwitch()
         */
        bool isSwitch() { return true; }

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
    };
}

#endif