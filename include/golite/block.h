#ifndef GOLITE_BLOCK_H
#define GOLITE_BLOCK_H

#include <vector>
#include <golite/statement.h>
#include <golite/break.h>
#include <golite/continue.h>

namespace golite {
    class Block : public Statement {
    private:
        std::vector<Statement*> statements_;
        int line_;

    public:
        Block(int line) : line_(line) {}

        /**
         * @see Statement::getLine()
         */
        int getLine() { return line_; }

        /**
         * Set statements
         * @param statements
         */
        void setStatements(std::vector<Statement*> statements) { statements_ = statements; }

        /**
         * Get statemetns
         * @return statements
         */
        const std::vector<Statement*> &getStatements() { return statements_; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::isBlock()
         */
        bool isBlock() { return true; }

        /**
         * Check recursively if block has a wrong break statement
         * @return ptr | nullptr
         */
        golite::Break* badBreak();

        /**
         * Check recursively if block has a wrong continue statement
         * @return ptr | nullptr
         */
        golite::Continue* badContinue();

        /**
         * Check recursively if block has a wrong assignment, declaration or variable declaration
         * @return ptr | nullptr
         */
        golite::Statement* badEquation();
    };
}

#endif
