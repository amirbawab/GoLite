#ifndef GOLITE_EXPRESSIONS_UNARY_H
#define GOLITE_EXPRESSIONS_UNARY_H

#include <golite/expression.h>

namespace golite {

    /**
     * Class representing unary expression
     * unary_expression: <operator> <expr>
     * operator:
     *     -
     *     !
     *     +
     *     ^
     */
    class Unary : public Expression {
    public:
        /**
         * All kinds of unary operators
         */
        enum KIND {
            MINUS,
            NOT,
            PLUS,
            XOR
        };

        Unary(Expression* operand, KIND kind) : operand_(operand), kind_(kind) {}

        /**
         * Get operand
         * @return operand
         */
        Expression* getOperand() const { return operand_; }

        /**
         * Get kind
         * @return kind
         */
        KIND getKind() const { kind_; }
    protected:
        Expression* operand_;
        KIND kind_;
    };
}

#endif
