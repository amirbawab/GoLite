#ifndef GOLITE_EXPRESSIONS_FUNCTION_CALL_H
#define GOLITE_EXPRESSIONS_FUNCTION_CALL_H

#include <vector>
#include <golite/expression.h>
#include <golite/identifier_expression.h>

namespace golite {
    // FIXME Update inheritance
    class FunctionCallExpression : public Expression {
    public:
        FunctionCallExpression(Expression* function, std::vector<Expression*>* args) {
            this->function_ = function;
            this->args_ = args;
        }
    protected:
        std::vector<Expression*>* args_;
        // TODO Not sure we still need this
        Expression* function_;
    };
}

#endif
