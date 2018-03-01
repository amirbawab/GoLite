#include <golite/expression_factory.h>

golite::Binary* golite::ExpressionFactory::createBPlus(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::PLUS);
}

golite::Binary* golite::ExpressionFactory::createBMinus(Expression *lhs, Expression *rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::MINUS);
}

golite::Binary* golite::ExpressionFactory::createBMultiply(Expression *lhs, Expression *rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::MULTIPLY);
}

golite::Binary* golite::ExpressionFactory::createBDivide(Expression *lhs, Expression *rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::DIVIDE);
}

golite::Binary* golite::ExpressionFactory::createBModulo(Expression *lhs, Expression *rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::MODULO);
}

golite::Binary* golite::ExpressionFactory::createBBitAND(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::BIT_AND);
}

golite::Binary* golite::ExpressionFactory::createBBitOR(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::BIT_OR);
}

golite::Binary* golite::ExpressionFactory::createBBitXOR(golite::Expression *lhs, golite::Expression *rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::BIT_XOR);
}

golite::Binary* golite::ExpressionFactory::createBBitClear(golite::Expression *lhs, golite::Expression *rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::BIT_CLEAR);
}

golite::Binary* golite::ExpressionFactory::createBLeftShift(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::LEFT_SHIFT);
}

golite::Binary* golite::ExpressionFactory::createBRightShift(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::RIGHT_SHIFT);
}

golite::Binary* golite::ExpressionFactory::createBIsEqual(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::IS_EQUAL);
}

golite::Binary* golite::ExpressionFactory::createBIsNotEqual(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::IS_NOT_EQUAL);
}

golite::Binary* golite::ExpressionFactory::createBLessThan(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::LESS_THAN);
}

golite::Binary* golite::ExpressionFactory::createBLessEqualThan(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::LESS_THAN_EQUAL);

}
golite::Binary* golite::ExpressionFactory::createBGreaterThan(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::GREATER_THAN);
}

golite::Binary* golite::ExpressionFactory::createBGreaterEqualThan(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::GREATER_THAN_EQUAL);
}

golite::Binary* golite::ExpressionFactory::createBAnd(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::AND);
}

golite::Binary* golite::ExpressionFactory::createBOr(golite::Expression* lhs, golite::Expression* rhs) {
    return new golite::Binary(lhs, rhs, golite::Binary::KIND::OR);
}

golite::Unary* golite::ExpressionFactory::createUMinus(golite::Expression* operand) {
    return new Unary(operand, Unary::KIND::MINUS);
}

golite::Unary* golite::ExpressionFactory::createUPlus(golite::Expression* operand) {
    return new Unary(operand, Unary::KIND::PLUS);
}

golite::Unary* golite::ExpressionFactory::createUNot(golite::Expression* operand) {
    return new Unary(operand, Unary::KIND::NOT);
}

golite::Unary* golite::ExpressionFactory::createUBitXOR(golite::Expression* operand) {
    return new Unary(operand, Unary::KIND::XOR);
}
