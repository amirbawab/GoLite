#ifndef GOLITE_BLOCK_H
#define GOLITE_BLOCK_H

#include <vector>
#include <golite/statement.h>

namespace golite {
    class Block : public Statement {
    protected:
        std::vector<Statement*> statements_;

    public:

        /**
         * Set statements
         * @param statements
         */
        void setStatements(std::vector<Statement*> statements) { statements_ = statements; }

        /**
         * Get statemetns
         * @return statements
         */
        std::vector<Statement*> getStatements() { return statements_; }

        /**
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);
    };
}

#endif
