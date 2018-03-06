#ifndef GOLITE_SYMBOL_H
#define GOLITE_SYMBOL_H

#include <golite/symbol_table.h>

namespace golite {
    class Symbol {
    public:
        /**
         * Performs a symbol table pass
         * @param root
         */
        virtual void symbolTablePass(SymbolTable* root) /*= 0*/ {};
    };
}

#endif