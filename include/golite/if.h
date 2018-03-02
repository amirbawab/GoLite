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
        Block* block_ = nullptr;
        Expression* expression_ = nullptr;
        std::vector<If*> else_if_;
        Block* else_ = nullptr;
        Simple* simple_ = nullptr;
        int line_;
    public:
        If(int line) : line_(line) {}

        /**
         * @see Statement::getLine()
         */
        int getLine() { return line_; }

        /**
         * Set else statement
         * @param block
         */
        void setElse(Block* block) { else_ = block; }

        /**
         * Set simple
         * @param simple
         */
        void setSimple(Simple* simple) { simple_ = simple; }

        /**
         * Set expression
         * @param expression
         */
        void setExpression(Expression* expression) { expression_ = expression; }

        /**
         * Set else if
         * @param else_if
         */
        void setElseIf(std::vector<If*> else_if) { else_if_ = else_if; }

        /**
         * Set block
         * @param block
         */
        void setBlock(Block* block) { block_ = block; }

        /**
         * Get block
         * @return block
         */
        Block* getBlock() const { return block_; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::isIf()
         */
        bool isIf() { return true; }

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        /**
         * @see Statement::typeCheck()
         */
        void typeCheck();
    };
}

#endif
