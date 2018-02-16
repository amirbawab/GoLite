#ifndef GOLITE_EXPRESSIONS_SLICE_H
#define GOLITE_EXPRESSIONS_SLICE_H

#include <expressions/expression.h>

namespace Golite::Expression {
    class SliceExpression : Expression {
    protected:
        Expression* start_;
        Expression* end_;
        Expression* skip_;
    };
}

#endif