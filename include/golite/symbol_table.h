#ifndef GOLITE_SYMBOL_TABLE
#define GOLITE_SYMBOL_TABLE

#include <map>
#include <string>
#include <vector>

namespace golite {
    class Symbol;

    class SymbolTable {
    private:
        SymbolTable* parent_;
        std::vector<SymbolTable*> children_; // symbol table may have multiple children
        std::map<std::string, Symbol*> entries_;

    public:
        SymbolTable() { this->parent_ = nullptr; }

        /**
         * Adds a Symbol table as a child to the current sym table
         * @param table
         */
        void addChild(SymbolTable* table);

        /**
         * Puts a new symbol in this sym table
         * @param name
         * @param decl
         */
        void putSymbol(std::string name, Symbol* decl);

        /**
         * Check whether the current sym table (or one of its parent, if specified) has a given symbol
         * @param name
         * @param search_in_parent
         * @return
         */
        bool hasSymbol(std::string name, bool search_in_parent = true);

        /**
         * Gets the symbol from the sym table (or one of its parent, if specified) for a given symbol
         * @param name
         * @param search_in_parent
         * @return
         */
        Symbol* getSymbol(std::string name, bool search_in_parent = true);
    };
}

#endif
