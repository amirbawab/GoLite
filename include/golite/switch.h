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

    public:

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
         * @return true if it does
         */
        golite::Continue* badContinue();

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