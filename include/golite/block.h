#ifndef GOLITE_BLOCK_H
#define GOLITE_BLOCK_H

#include <vector>
#include <golite/statement.h>

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
        golite::Statement* badBreak();

        /**
         * Check recursively if block has a wrong continue statement
         * @return ptr | nullptr
         */
        golite::Statement* badContinue();

        /**
         * Check recursively if block has a wrong assignment, declaration or variable declaration
         * @return ptr | nullptr
         */
        golite::Statement* badEquation();

        /**
         * Bad statment
         * @return ptr | nullptr
         */
        golite::Statement* badStatement();

        /**
         * Bad declaration
         * @return ptr | nullptr
         */
        golite::Statement* badDeclaration();

        /**
         * Bad declaration
         * @return ptr | nullptr
         */
        golite::Statement* badSwitch();

        /**
         * Bad blank
         * @return ptr | nullptr
         */
        golite::Statement* badBlank();
    };
}

#endif
