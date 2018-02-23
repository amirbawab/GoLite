#ifndef GOLITE_EXPRESSIONS_INDEX_H
#define GOLITE_EXPRESSIONS_INDEX_H

#include <golite/expression.h>

namespace golite {
    class IndexExpression : public Expression {
    public:
        IndexExpression(Expression* target, Expression* idx) {
            this->target_ = target;
            this->expression_ = idx;
        }
    protected:
        Expression* target_;
        Expression* expression_;
    };
}

#endif
