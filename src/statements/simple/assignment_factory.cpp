#include <golite/assignment_factory.h>

golite::Assignment* golite::AssignmentFactory::createEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createPlusEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::PLUS_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createMinusEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::MINUS_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createMultiplyEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::MULTIPLY_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createDivideEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::DIVIDE_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createModuloEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::MODULO_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createLeftShiftEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::LEFT_SHIFT_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createRightShiftEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::RIGHT_SHIFT_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createBitANDEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::BIT_AND_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createBitOREqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::BIT_OR_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createBitXOREqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::BIT_XOR_EQUAL);
}

golite::Assignment* golite::AssignmentFactory::createBitClearEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs) {
    return new golite::Assignment(lhs, rhs, Assignment::KIND::BIT_CLEAR_EQUAL);
}
