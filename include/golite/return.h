#ifndef GOLITE_RETURN_H
#define GOLITE_RETURN_H

#include <golite/expression.h>

namespace golite {
    class Return : public Statement {
    private:
        Expression* expression_;
    public:

        /**
         * Get expression
         * @return expression
         */
        Expression* getExpression() { return expression_; }

        /**
         * Set expression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression;}
    };
}

#endif