#ifndef GOLITE_EXPRESSIONS_IDENTIFIER_H
#define GOLITE_EXPRESSIONS_IDENTIFIER_H

#include <string>
#include <golite/expressions/expression.h>

namespace golite {
    class IdentifierExpression : Expression {
    protected:
        std::string name_;
    };
}

#endif