#ifndef GOLITE_EXPRESSIONS_LITERAL_H
#define GOLITE_EXPRESSIONS_LITERAL_H

#include <golite/expressions/expression.h>

namespace golite {
    template <class T>
    class LiteralExpression : public Expression {
    public:
        LiteralExpression(T val, int line): Expression(line) {
            this->value_ = val;
        }
    protected:
        T value_;
    };
}

#endif