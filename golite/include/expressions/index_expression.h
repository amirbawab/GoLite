#ifndef GOLITE_EXPRESSIONS_INDEX_H
#define GOLITE_EXPRESSIONS_INDEX_H

#include <expressions/expression.h>

namespace Golite::Expression {
    class IndexExpression : Expression {
    protected:
        Expression* expression_;
    };
}

#endif