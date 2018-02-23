#ifndef GOLITE_STATEMENTS_IF_H
#define GOLITE_STATEMENTS_IF_H

#include <golite/simple.h>
#include <golite/block.h>
#include <golite/expression.h>

namespace golite {

    /**
     * If statement with optional else if and else statements
     */
    class If : public Statement {
    private:
        Block block_;
        Expression* expression_;
        std::vector<If*> else_if_;
        Block* else_;
        Simple* simple_;

    public:

        /**
         * Get block reference
         * @return block
         */
        Block& getBlock() {return block_;}

        /**
         * Get else statement
         * @return else statement
         */
        Block* getElse() const { return else_;}

        /**
         * Set else statement
         * @param block
         */
        void setElse(Block* block) { else_ = block; }

        /**
         * Get simple
         * @return simple
         */
        Simple* getSimple() const { return simple_; }

        /**
         * Set simple
         * @param simple
         */
        void setSimple(Simple* simple) { simple_ = simple; }

        /**
         * Get else if vector
         * @return vector
         */
        std::vector<If*> getElseIf() {return else_if_; }

        /**
         * Add else if statement
         * @param elseIf
         */
        void addElseIf(If* elseIf);

        /**
         * Get expression
         * @return expression
         */
        Expression* getExpression() const { return expression_; }

        /**
         * Set expression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression; }
    };
}

#endif
