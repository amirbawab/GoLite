#ifndef GOLITE_STATEMENTS_FOR_H
#define GOLITE_STATEMENTS_FOR_H

#include <golite/simple.h>
#include <golite/block.h>
#include <golite/expression.h>

namespace golite {
    class ForStatement : public Statement {
    private:
        Block block_;
        Simple* left_simple_;
        Simple* right_simple_;
        Expression* expression_;
    public:

        /**
         * Get block
         * @return block reference
         */
        Block& getBlock() { return block_; }

        /**
         * Set left simple
         * @param left_simple
         */
        void setLeftSimple(Simple* left_simple) { left_simple_ = left_simple; }

        /**
         * Set right simple
         * @param right_simple
         */
        void setRightSimple(Simple* right_simple) { right_simple_ = right_simple; }

        /**
         * Set expression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression; }

        /**
         * Get expression
         * @return expression
         */
        Expression* getExpression() { return expression_; }

        /**
         * Get left simple
         * @return left simple
         */
        Simple* getLeftSimple() { return left_simple_; }

        /**
         * Get right simple
         * @return right simple
         */
        Simple* getRightSimple() {return right_simple_; }
    };
}

#endif
