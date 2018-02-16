#ifndef GOLITE_EXPRESSIONS_FUNCTION_CALL_H
#define GOLITE_EXPRESSIONS_FUNCTION_CALL_H

#include <vector>
#include <expressions/expression.h>
#include <expressions/identifier_expression.h>

using namespace std;

namespace Golite::Expression {
    class FunctionCallExpression : Expression {
    protected:
        vector<Expression*> args_;
        IdentifierExpression* identifier_;
    };
}

#endif