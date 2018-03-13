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
        std::map<std::string, SymbolTable*> tables_;
        std::map<std::string, Declarable*> entries_;
        std::vector<std::string> entries_keys_;
        const std::string init_prefix = "~init~";

    public:
        SymbolTable(SymbolTable* parent);

        /**
         * Puts a new symbol in this sym table
         * @param name
         * @param decl
         */
        void putSymbol(std::string name, Declarable* decl);

        /**
         * Puts init in symbol table
         * @param decl
         */
        void putInit(Declarable* decl);

        /**
         * Puts a new table
         * @param table
         */
        void putTable(SymbolTable* table);

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

        /**
         * Update the symbol from the sym table (or one of its parent, if specified) for a given symbol
         * @param name
         * @param new_declarable
         * @param search_in_parent
         * @return void
         */
        void updateSymbol(std::string name, Declarable* new_declarable, bool search_in_parent = true);

        /**
         * Gets the symbol table from the sym table (or one of its parent, if specified) for a given symbol
         * @param name
         * @param search_in_parent
         * @return
         */
        SymbolTable* getSymbolTable(std::string name, bool search_in_parent = true);

        /**
         * Prettify symbol table
         * @param indent
         * @return string
         */
        std::string toPrettySymbol(int indent);
    };
}

#endif
