#ifndef GOLITE_SYMBOL_TABLE
#define GOLITE_SYMBOL_TABLE

#include <map>
#include <string>
#include <golite/declarable.h>

namespace golite {
    class SymbolTable {
    protected:
        SymbolTable* parent_;
        std::map<std::string, Declarable*> entries_;
    };
}

#endif
