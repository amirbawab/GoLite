#ifndef GOLITE_STATEMENTS_DECLARABLES_TYPE_H
#define GOLITE_STATEMENTS_DECLARABLES_TYPE_H

#include <golite/statement.h>
#include <golite/declarable.h>
#include <golite/identifier.h>
#include <golite/type_component.h>

namespace golite {
    class Type : public Declarable, public Statement {
    private:
        Identifier* identifier_ = nullptr;
        TypeComponent* type_component_ = nullptr;
    public:
        Type(Identifier* identifier, TypeComponent* type_component) :
                identifier_(identifier), type_component_(type_component){}

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
         * Get tyep component
         * @return type component
         */
        TypeComponent* getTypeComponent() const { return type_component_; }

        /**
         * Set type component
         * @param type_component
         */
        void setTypeComponent(TypeComponent* type_component) { type_component_ = type_component; }

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
    };
}

#endif
