#ifndef GOLITE_SCOPE_SCOPE_H
#define GOLITE_SCOPE_SCOPE_H

#include <vector>
#include <golite/statements/statement.h>
#include <golite/symbol_table.h>

namespace golite {
    class Scope {
    public:
        Scope();
    protected:
        std::vector<Statement*>* statements_;
        SymbolTable symbol_table_;
    };
}

#endif