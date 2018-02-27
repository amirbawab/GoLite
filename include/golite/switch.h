#ifndef GOLITE_SWITCH_H
#define GOLITE_SWITCH_H

#include <vector>
#include <golite/expression.h>
#include <golite/switch_case.h>

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
         * Check for bad usage of continue statement
         * @return ptr | nullptr
         */
        golite::Continue* badContinue();

        /**
         * Check for bad usage of continue statement
         * @return ptr | nullptr
         */
        golite::Statement* badStatement();

        /**
         * Check for bad usage of declaration statement
         * @return ptr | nullptr
         */
        golite::Declaration* badDeclaration();

        /**
         * Check for bad usage of switch default
         * @return ptr | nullptr
         */
        golite::SwitchCase* badDefault();

        /**
         * Check for bad usage of switch
         * @return ptr | nullptr
         */
        golite::Statement* badSwitch();

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::isSwitch()
         */
        bool isSwitch() { return true; }
    };
}

#endif