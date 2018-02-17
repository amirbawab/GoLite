#ifndef GOLITE_EXPRESSIONS_LITERAL_H
#define GOLITE_EXPRESSIONS_LITERAL_H

#include <golite/expressions/expression.h>

namespace golite {
    template <class T>
    class LiteralExpression : Expression {
    protected:
        T value_;
    };
}

#endif