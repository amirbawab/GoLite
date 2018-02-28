#ifndef GOLITE_SWITCH_CASE_H
#define GOLITE_SWITCH_CASE_H

#include <vector>
#include <golite/expression.h>
#include <golite/block.h>
#include <golite/statement.h>

namespace golite {
    class SwitchCase {
    private:
        std::vector<Expression*> expressions_;
        Block* block_ = nullptr;
    public:

        /**
         * Check if default case
         * @return true if default case
         */
        bool isDefault() {
            return expressions_.empty();
        }

        /**
         * Set expressions
         * @param expressions
         */
        void setExpressions(std::vector<Expression*> expressions) { expressions_ = expressions; }

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
         * Conver to GoLite
         * @param indent
         * @return golite code
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::getLine()
         */
        int getLine();

        /**
         * Perform a weeding pass
         * @param check_break
         * @param check_continue
         */
        void weedingPass(bool check_break, bool check_continue);
    };
}

#endif