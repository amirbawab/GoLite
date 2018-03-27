#ifndef GOLITE_IDENTIFIER_H
#define GOLITE_IDENTIFIER_H

#include <string>
#include <golite/primary.h>

namespace golite {
    class Identifier : public Primary {
    private:
        static std::string BLANK;
        std::string name_;
        std::string ts_name_;
        int line_;
        SymbolTable* symbol_table_ = nullptr;
    public:
        Identifier(std::string name, int line) : name_(name), line_(line) {}

        /**
         * Get name
         * @return name
         */
        std::string getName() const { return name_; }

        /**
         * Get line
         * @return line
         */
        int getLine() { return line_; }

        /**
         * @see Expression::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @ee Expression::isIdentifier()
         */
        bool isIdentifier() { return true; }

        /**
         * Check if identifier is a blank identifier
         * @return true if it is
         */
        bool isBlank();

        /**
         * @see Expression::weedingPass()
         */
        void weedingPass();

        /**
         * @see Expression::typeCheck()
         */
        golite::TypeComponent* typeCheck();

        /**
         * @see Statement::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * Update symbol table entry for inferred types
         * @param new_type
         * @param search_in_parent
         */
        void updateTypeInSymbolTable(TypeComponent* new_type, bool search_in_parent = true);

        /**
         * Get symbol table entry
         * @return declarable
         */
        Declarable* getSymbolTableEntry();

        /**
         * @see Expression::isCasting()
         */
        bool isCasting();

        /**
         * @see Expression::toTypeScript()
         */
        std::string toTypeScript(int indent);

        /**
         * @see Expression::toTypeScriptInitializer()
         */
        std::string toTypeScriptInitializer(int indent);

        /**
         * Set symbol table
         * @param symbol_table
         */
        void setSymbolTable(SymbolTable* symbol_table) { symbol_table_ = symbol_table; }
    };
}

#endif