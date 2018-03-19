#ifndef GOLITE_STATEMENTS_DECLARABLES_TYPE_H
#define GOLITE_STATEMENTS_DECLARABLES_TYPE_H

#include <golite/statement.h>
#include <golite/declarable.h>
#include <golite/identifier.h>

namespace golite {
    class Type : public Declarable, public Statement {
    private:
        Identifier* identifier_ = nullptr;
    public:
        Type(Identifier* identifier, TypeComponent* type_component);

        /**
         * Get identifier
         * @return identifier
         */
        Identifier* getIdentifier() const { return identifier_; }

        /**
         * Set identifier
         * @param identifier
         */
        void setIdentifier(Identifier* identifier) { identifier_ = identifier; }

        /**
         * @see Declarable::isTypeDeclaration()
         */
        bool isTypeDeclaration() {  return true; }

        /**
         * @see Declarable::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see Statement::getLine()
         */
        int getLine();

        /**
         * @see Statement::weedingPass()
         */
        void weedingPass(bool check_break, bool check_continue);

        /**
         * @see Statement::typeCheck()
         */
        void typeCheck();

        /*
         * @see Declarable::symbolTablePass()
         */
        void symbolTablePass(SymbolTable *root);

        /*
         * Check if it's a recursive type
         */
        bool isRecursive();

        /**
         * @see Declarable::toPrettySymbol()
         */
        std::string toPrettySymbol();

        /**
         * Check if type component contains a self refence
         * @return
         */
        bool isSelfReferring();

        /**
         * Create a type component from this type
         * @return type component
         */
        TypeComponent* toTypeComponent();

        /**
         * @see Declarable::toTypeScript()
         */
        std::string toTypeScript(int indent);
    };
}

#endif
