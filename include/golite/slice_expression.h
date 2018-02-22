#ifndef GOLITE_EXPRESSIONS_SLICE_H
#define GOLITE_EXPRESSIONS_SLICE_H

#include <golite/expressions/expression.h>

namespace golite {
    class SliceExpression : Expression {
    protected:
        Expression* start_;
        Expression* end_;
        Expression* skip_;
    };
}

#endif