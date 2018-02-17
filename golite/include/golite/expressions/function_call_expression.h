#ifndef GOLITE_EXPRESSIONS_FUNCTION_CALL_H
#define GOLITE_EXPRESSIONS_FUNCTION_CALL_H

#include <vector>
#include <golite/expressions/expression.h>
#include <golite/expressions/identifier_expression.h>

namespace golite {
    class FunctionCallExpression : Expression {
    protected:
        std::vector<Expression*> args_;
        IdentifierExpression* identifier_;
    };
}

#endif