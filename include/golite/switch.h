#ifndef GOLITE_SWITCH_H
#define GOLITE_SWITCH_H

#include <vector>
#include <golite/expression.h>
#include <golite/switch_case.h>

namespace golite {
    class Switch : public Statement {
    private:
        Simple* simple_;
        Expression* expression_;
        std::vector<SwitchCase*> cases_;

    public:

        /**
         * Get simple
         * @return simple
         */
        Simple* getSimple() const { return simple_; }

        /**
         * Set simple
         * @param simple
         */
        void setSimple(Simple* simple) { simple_ = simple; }

        /**
         * Get expression
         * @return expression
         */
        Expression* getExpression() const { return expression_; }

        /**
         * Set epression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression;}
    };
}

#endif