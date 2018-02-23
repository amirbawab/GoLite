#ifndef GOLITE_SCOPE_SCOPE_H
#define GOLITE_SCOPE_SCOPE_H

#include <vector>
#include <golite/statement.h>
#include <golite/symbol_table.h>

namespace golite {
    class Block : public Statement {
    public:
        Block();

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
        SymbolTable symbol_table_;
    };
}

#endif
