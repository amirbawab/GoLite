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
        static BinaryExpression* createBPlus(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBMinus(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBMultiply(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBDivide(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBModulo(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBBitAND(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBBitOR(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBBitXOR(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBBitClear(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBLeftShift(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBRightShift(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBIsEquals(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBIsNotEquals(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBLessThan(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBLessEqualThan(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBGreaterThan(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBGreaterEqualThan(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBAnd(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBOr(Expression* lhs, Expression* rhs);
        static BinaryExpression* createBDot(Expression* lhs, Expression* rhs);

        static UnaryExpression* createUMinus(Expression* operand);
        static UnaryExpression* createUPlus(Expression* operand);
        static UnaryExpression* createUNot(Expression* operand);
        static UnaryExpression* createUBitXOR(Expression* operand);

        static FunctionCallExpression* createFunctionCall(Expression* identifier, std::vector<Expression*>* args);
        static IndexExpression* createIndexExpr(Expression* target, Expression* idx);
    };
}

#endif
