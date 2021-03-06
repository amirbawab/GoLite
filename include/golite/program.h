#ifndef GOLITE_SCOPE_PROGRAM_H
#define GOLITE_SCOPE_PROGRAM_H

#include <string>
#include <stack>
#include <golite/declarable.h>
#include <golite/identifier.h>
#include <golite/symbol_table.h>
#include <golite/type.h>
#include <golite/variable.h>

namespace golite {

    /**
     * Singleton class
     *
     * Program instance and entry point to the input AST
     */
    class Program {
    private:
        Program(){}
        Identifier* package_name_ = nullptr;
        std::vector<Declarable*> declarables_;
        SymbolTable* root_symbol_table_ = nullptr;
        SymbolTable* program_symbol_table_ = nullptr;

        void initializeSymbolTable();
    public:
        static Type* INT_BUILTIN_TYPE;
        static Type* FLOAT64_BUILTIN_TYPE;
        static Type* RUNE_BUILTIN_TYPE;
        static Type* BOOL_BUILTIN_TYPE;
        static Type* STRING_BUILTIN_TYPE;
        static Type* VOID_TYPE;
        static Type* INFER_TYPE;
        static Type* UNMAPPED_TYPE;
        static Variable* TRUE_VAR;
        static Variable* FALSE_VAR;
        static std::string INIT_FUNC_NAME;
        static std::string MAIN_FUNC_NAME;

        static Program* getInstance() {
            static Program* instance(new Program());
            return instance;
        }

        // Delete constructor and operator
        Program(Program const&) = delete;
        void operator=(Program const&) = delete;

        /**
         * Set package name
         * @param package_name
         */
        void setPackageName(Identifier* package_name) {package_name_ = package_name;}

        /**
         * Get package name
         * @return package name
         */
        Identifier* getPackageName() const { return package_name_; }

        /**
         * Set declarables
         * @param declarables
         */
        void setDeclarables(std::vector<Declarable*> declarables) { declarables_ = declarables; }

        /**
         * Convert to golite
         * @param indent
         * @return golite code
         */
        std::string toGoLite(int indent);

        /**
         * Perform a weeding pass to detect errors
         */
        void weedingPass();

        /**
         * Perform a symbol table pass to detect errors
         */
        void symbolTablePass();

        /**
         * Perform type checking on all declarable
         */
        void typeCheck();

        /**
         * Get prettified symbol table
         * @param indent
         * @return symbol table string representation
         */
        std::string prettifySymbolTable(int indent);

        /**
         * Get program symbol table
         * @return symbol table
         */
        SymbolTable* getProgramSymbolTable() { return program_symbol_table_; }

        /**
         * Generate typescript code
         * @return code
         */
        std::string toTypeScript(int indent);
    };
}

#endif
