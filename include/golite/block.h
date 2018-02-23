#ifndef GOLITE_BLCOK_H
#define GOLITE_BLOCK_H

#include <vector>
#include <golite/statement.h>

namespace golite {
    class Block : public Statement {
    public:

        /**
         * Set statements
         * @param statements
         */
        void setStatements(std::vector<Statement*> statements) { statements_ = statements; }

        /**
         * Get statements
         * @return statements vector
         */
        std::vector<Statement*> getStatements() {return statements_;}

    protected:
        std::vector<Statement*> statements_;
    };
}

#endif
