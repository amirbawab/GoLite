#ifndef GOLITE_EXPRESSIONS_INDEX_H
#define GOLITE_EXPRESSIONS_INDEX_H

#include <golite/expressions/expression.h>

namespace golite {
    class IndexExpression : Expression {
    protected:
        Expression* expression_;
    };
}

#endif