#ifndef GOLITE_EXPRESSIONS_EXPRESSION_FACTORY_H
#define GOLITE_EXPRESSIONS_EXPRESSION_FACTORY_H

#include <vector>

#include <golite/expression.h>
#include <golite/binary.h>
#include <golite/unary.h>
#include <golite/function_call.h>
#include <golite/index.h>

namespace golite {
    class ExpressionFactory {
    public:
        static Binary* createBPlus(Expression* lhs, Expression* rhs);
        static Binary* createBMinus(Expression* lhs, Expression* rhs);
        static Binary* createBMultiply(Expression* lhs, Expression* rhs);
        static Binary* createBDivide(Expression* lhs, Expression* rhs);
        static Binary* createBModulo(Expression* lhs, Expression* rhs);
        static Binary* createBBitAND(Expression* lhs, Expression* rhs);
        static Binary* createBBitOR(Expression* lhs, Expression* rhs);
        static Binary* createBBitXOR(Expression* lhs, Expression* rhs);
        static Binary* createBBitClear(Expression* lhs, Expression* rhs);
        static Binary* createBLeftShift(Expression* lhs, Expression* rhs);
        static Binary* createBRightShift(Expression* lhs, Expression* rhs);
        static Binary* createBIsEqual(Expression* lhs, Expression* rhs);
        static Binary* createBIsNotEqual(Expression* lhs, Expression* rhs);
        static Binary* createBLessThan(Expression* lhs, Expression* rhs);
        static Binary* createBLessEqualThan(Expression* lhs, Expression* rhs);
        static Binary* createBGreaterThan(Expression* lhs, Expression* rhs);
        static Binary* createBGreaterEqualThan(Expression* lhs, Expression* rhs);
        static Binary* createBAnd(Expression* lhs, Expression* rhs);
        static Binary* createBOr(Expression* lhs, Expression* rhs);

        static Unary* createUMinus(Expression* operand);
        static Unary* createUPlus(Expression* operand);
        static Unary* createUNot(Expression* operand);
        static Unary* createUBitXOR(Expression* operand);
    };
}

#endif
