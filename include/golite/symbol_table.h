#ifndef GOLITE_SYMBOL_TABLE
#define GOLITE_SYMBOL_TABLE

#include <sstream>
#include <map>
#include <string>
#include <vector>

namespace golite {
    class Declarable;

    class SymbolTable {
    private:
        SymbolTable* parent_ = nullptr;
        std::vector<SymbolTable*> children_; // symbol table may have multiple children
        std::map<std::string, Declarable*> entries_;

    public:
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
        void putSymbol(std::string name, Declarable* decl);

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
        Declarable* getSymbol(std::string name, bool search_in_parent = true);

        std::string prettyPrint(int indent = 0);
    };
}

#endif
