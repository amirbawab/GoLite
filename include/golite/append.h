#ifndef GOLITE_APPEND_H
#define GOLITE_APPEND_H

#include <vector>
#include <golite/expression.h>

namespace golite {
    class Append : public Expression {
    public:
        Append(Expression* left_expression, Expression* right_expression) :
                left_expression_(left_expression), right_expression_(right_expression){}

        /**
         * Get left expression
         * @return expression
         */
        Expression* getLeftExpression() const { return left_expression_; }

        /**
         * Get right expression
         * @return expression
         */
        Expression* getRightExpression() const { return right_expression_; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);
    private:
        Expression* left_expression_;
        Expression* right_expression_;
    };
}

#endif
