#ifndef GOLITE_EXPRESSIONS_INDEX_H
#define GOLITE_EXPRESSIONS_INDEX_H

#include <golite/primary.h>

namespace golite {
    class Index : public Primary {
    private:
        Expression* expression_;
    public:
        Index(Expression* expression) : expression_(expression) {}

        /**
         * Set expression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression; }

        /**
         * Get expression
         * @return expression
         */
        Expression* getExpression() const { return expression_; }
    };
}

#endif
