#ifndef GOLITE_STATEMENTS_FOR_H
#define GOLITE_STATEMENTS_FOR_H

#include <golite/simple.h>
#include <golite/block.h>
#include <golite/expression.h>

namespace golite {
    class For : public Statement {
    private:
        Block* block_ = nullptr;
        Simple* left_simple_ = nullptr;
        Simple* right_simple_ = nullptr;
        Expression* expression_ = nullptr;
        int line_;
    public:
        For(int line) : line_(line) {}

        /**
         * @see Statement::getLine()
         */
        int getLine() { return line_; }

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
         * @see  Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::isFor()
         */
        bool isFor() { return true; }

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        /**
         * @see Statement::typeCheck()
         */
        void typeCheck();

        /*
         * @see Statement::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * @see Statement::hasReturn()
         */
        bool hasReturn(Declarable* function);

        /**
         * @see Statement::hsaBreak()
         */
        bool hasBreak();

        /**
         * @see Statement::isTerminating()
         */
        bool isTerminating();
    };
}

#endif
