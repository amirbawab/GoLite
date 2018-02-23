#include <golite/expression_factory.h>

using namespace golite;

Binary* ExpressionFactory::createBPlus(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::PLUS);
}

Binary* ExpressionFactory::createBMinus(Expression *lhs, Expression *rhs) {
    return new Binary(lhs, rhs, Binary::KIND::MINUS);
}

Binary* ExpressionFactory::createBMultiply(Expression *lhs, Expression *rhs) {
    return new Binary(lhs, rhs, Binary::KIND::MULTIPLY);
}

Binary* ExpressionFactory::createBDivide(Expression *lhs, Expression *rhs) {
    return new Binary(lhs, rhs, Binary::KIND::DIVIDE);
}

Binary* ExpressionFactory::createBModulo(Expression *lhs, Expression *rhs) {
    return new Binary(lhs, rhs, Binary::KIND::MODULO);
}

Binary *ExpressionFactory::createBBitAND(Expression *lhs, Expression *rhs) {
    return new Binary(lhs, rhs, Binary::KIND::BIT_AND);
}

Binary *ExpressionFactory::createBBitOR(Expression *lhs, Expression *rhs) {
    return new Binary(lhs, rhs, Binary::KIND::BIT_OR);
}

Binary *ExpressionFactory::createBBitXOR(Expression *lhs, Expression *rhs) {
    return new Binary(lhs, rhs, Binary::KIND::BIT_XOR);
}

Binary *ExpressionFactory::createBBitClear(Expression *lhs, Expression *rhs) {
    return new Binary(lhs, rhs, Binary::KIND::BIT_CLEAR);
}

Binary* ExpressionFactory::createBLeftShift(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::LEFT_SHIFT);
}

Binary* ExpressionFactory::createBRightShift(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::RIGHT_SHIFT);
}

Binary* ExpressionFactory::createBIsEquals(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::IS_EQUAL);
}

Binary* ExpressionFactory::createBIsNotEquals(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::IS_NOT_EQUAL);
}

Binary* ExpressionFactory::createBLessThan(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::LESS_THAN);
}

Binary* ExpressionFactory::createBLessEqualThan(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::LESS_THAN_EQUAL);

}
Binary* ExpressionFactory::createBGreaterThan(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::GREATER_THAN);
}

Binary* ExpressionFactory::createBGreaterEqualThan(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::GREATER_THAN_EQUAL);
}

Binary* ExpressionFactory::createBAnd(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::AND);
}

Binary* ExpressionFactory::createBOr(Expression* lhs, Expression* rhs) {
    return new Binary(lhs, rhs, Binary::KIND::OR);
}

Unary* ExpressionFactory::createUMinus(Expression* operand) {
    return new Unary(operand, Unary::KIND::MINUS);
}

Unary* ExpressionFactory::createUPlus(Expression* operand) {
    return new Unary(operand, Unary::KIND::PLUS);
}

Unary* ExpressionFactory::createUNot(Expression* operand) {
    return new Unary(operand, Unary::KIND::NOT);
}

Unary* ExpressionFactory::createUBitXOR(Expression* operand) {
    return new Unary(operand, Unary::KIND::XOR);
}
