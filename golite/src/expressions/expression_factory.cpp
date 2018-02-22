#include <golite/expressions/expression_factory.h>

using namespace golite;

BinaryExpression* ExpressionFactory::createBPlus(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_PLUS);
}

BinaryExpression* ExpressionFactory::createBMinus(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_MINUS);
}

BinaryExpression* ExpressionFactory::createBMultiply(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_MULTIPLY);
}

BinaryExpression* ExpressionFactory::createBDivide(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_DIVIDE);
}

BinaryExpression* ExpressionFactory::createBModulo(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_MODULO);
}

BinaryExpression *ExpressionFactory::createBBitAND(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_BIT_AND);
}

BinaryExpression *ExpressionFactory::createBBitOR(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_BIT_OR);
}

BinaryExpression *ExpressionFactory::createBBitXOR(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_BIT_XOR);
}

BinaryExpression *ExpressionFactory::createBBitClear(Expression *lhs, Expression *rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_BIT_CLEAR);
}

BinaryExpression* ExpressionFactory::createBLeftShift(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_LEFT_SHIFT);
}

BinaryExpression* ExpressionFactory::createBRightShift(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_RIGHT_SHIFT);
}

BinaryExpression* ExpressionFactory::createBIsEquals(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_IS_EQUAL);
}

BinaryExpression* ExpressionFactory::createBIsNotEquals(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_IS_NOT_EQUAL);
}

BinaryExpression* ExpressionFactory::createBLessThan(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_LESS_THAN);
}

BinaryExpression* ExpressionFactory::createBLessEqualThan(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_LESS_THAN_EQUAL);

}
BinaryExpression* ExpressionFactory::createBGreaterThan(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_GREATER_THAN);
}

BinaryExpression* ExpressionFactory::createBGreaterEqualThan(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_GREATER_THAN_EQUAL);
}

BinaryExpression* ExpressionFactory::createBAnd(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_AND);
}

BinaryExpression* ExpressionFactory::createBOr(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_OR);
}

BinaryExpression* ExpressionFactory::createBDot(Expression* lhs, Expression* rhs) {
    return new BinaryExpression(lhs, rhs, BinaryExpressionType::BINARY_DOT);
}

UnaryExpression* ExpressionFactory::createUMinus(Expression* operand) {
    return new UnaryExpression(operand, UnaryExpressionType::UNARY_MINUS);
}

UnaryExpression* ExpressionFactory::createUPlus(Expression* operand) {
    return new UnaryExpression(operand, UnaryExpressionType::UNARY_PLUS);
}

UnaryExpression* ExpressionFactory::createUNot(Expression* operand) {
    return new UnaryExpression(operand, UnaryExpressionType::UNARY_NOT);
}

UnaryExpression* ExpressionFactory::createUBitXOR(Expression* operand) {
    return new UnaryExpression(operand, UnaryExpressionType::UNARY_XOR);
}

FunctionCallExpression* ExpressionFactory::createFunctionCall(Expression* fn, std::vector<Expression*>* args) {
    return new FunctionCallExpression(fn, args);
}

IndexExpression* ExpressionFactory::createIndexExpr(Expression* target, Expression* idx) {
    return new IndexExpression(target, idx);
}