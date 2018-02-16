#ifndef GOLITE_EXPRESSIONS_LITERAL_H
#define GOLITE_EXPRESSIONS_LITERAL_H

#include <expressions/expression.h>

namespace Golite::Expression {
    template <class T>
    class LiteralExpression<T> : Expression {
    protected:
        T value_;
    };
}

#endif