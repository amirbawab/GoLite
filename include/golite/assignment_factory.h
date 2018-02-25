#ifndef GOLITE_ASSIGNMENT_FACTORY_H
#define GOLITE_ASSIGNMENT_FACTORY_H

#include <vector>

#include <golite/assignment.h>

namespace golite {
    class AssignmentFactory {
    public:
        static Assignment* createEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createPlusEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createMinusEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createMultiplyEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createDivideEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createModuloEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createLeftShiftEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createRightShiftEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createBitANDEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createBitOREqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createBitXOREqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
        static Assignment* createBitClearEqual(std::vector<Expression*> lhs, std::vector<Expression*> rhs);
    };
}

#endif
