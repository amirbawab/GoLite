#include <golite/expressions/expression_factory.h>

using namespace golite;

BinaryExpression* ExpressionFactory::createBPlus(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::PLUS);
}

BinaryExpression* ExpressionFactory::createBMinus(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::MINUS);
}

BinaryExpression* ExpressionFactory::createBMultiply(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::MULTIPLY);
}

BinaryExpression* ExpressionFactory::createBDivide(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::DIVIDE);
}

BinaryExpression* ExpressionFactory::createBModulo(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::MODULO);
}

BinaryExpression *ExpressionFactory::createBBitAND(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BIT_AND);
}

BinaryExpression *ExpressionFactory::createBBitOR(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BIT_OR);
}

BinaryExpression *ExpressionFactory::createBBitXOR(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BIT_XOR);
}

BinaryExpression *ExpressionFactory::createBBitClear(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BIT_CLEAR);
}

BinaryExpression* ExpressionFactory::createBLeftShift(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::LEFT_SHIFT);
}

BinaryExpression* ExpressionFactory::createBRightShift(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::RIGHT_SHIFT);
}

BinaryExpression* ExpressionFactory::createBIsEquals(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::IS_EQUAL);
}

BinaryExpression* ExpressionFactory::createBIsNotEquals(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::IS_NOT_EQUAL);
}

BinaryExpression* ExpressionFactory::createBLessThan(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::LESS_THAN);
}

BinaryExpression* ExpressionFactory::createBLessEqualThan(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::LESS_THAN_EQUAL);

}
BinaryExpression* ExpressionFactory::createBGreaterThan(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::GREATER_THAN);
}

BinaryExpression* ExpressionFactory::createBGreaterEqualThan(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::GREATER_THAN_EQUAL);
}

BinaryExpression* ExpressionFactory::createBAnd(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::AND);
}

BinaryExpression* ExpressionFactory::createBOr(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::OR);
}

BinaryExpression* ExpressionFactory::createBDot(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::DOT);
}