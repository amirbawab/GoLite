#ifndef GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H
#define GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H

#include <string>
#include <golite/type_component.h>
#include <golite/symbol_table.h>

namespace golite {
    /**
     * Parent class of elements that can be created on the global scope (program scope)
     *
     * The following types can are declarable on the global scope:
     * - Types
     * - Variables
     * - Functions
     */
    class Declarable {
    protected:
        TypeComponent* type_component_ = nullptr;
    public:

        /**
         * Convert code to golite
         * @param indent
         * @return code
         */
        virtual std::string toGoLite(int indent) = 0;

        /**
         * Function overrides this function
         * @return true for functions
         */
        virtual bool isFunction() { return false; }

        /**
         * Variable overrides this function
         * @return true for variable statements
         */
        virtual bool isDecVariable() { return false; }

        /**
         * Type decl overrides this function
         * @return true for type
         */
        virtual bool isTypeDeclaration() {  return false; }

        /**
         * @see Statement::weedingPass()
         */
        virtual void weedingPass(bool check_break, bool check_continue) = 0;

        /**
         * @see Statement::typeCheck()
         */
        virtual void typeCheck() = 0;

        /**
         * @see Statement::symbolTablePass()
         */
        virtual void symbolTablePass(SymbolTable* root) = 0;

        /**
         * Gets the pretty symbol
         */
        virtual std::string toPrettySymbol() = 0;

        /**
         * Get line
         * @return line
         */
        virtual int getLine() = 0;

        /**
         * Set type component
         * @param type_component
         */
        void setTypeComponent(golite::TypeComponent* type_component) { type_component_ = type_component; }

        /**
         * Get type component
         * @return type component
         */
        golite::TypeComponent* getTypeComponent() const { return type_component_; }

        /**
         * Generate typescript code
         * @return code
         */
        virtual std::string toTypeScript(int indent) = 0;
    };
}

#endif
