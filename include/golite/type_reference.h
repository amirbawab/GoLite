#ifndef GOLITE_TYPE_REFERENCE_H
#define GOLITE_TYPE_REFERENCE_H

#include <golite/type_composite.h>
#include <golite/type.h>

namespace golite {
    class TypeReference : public TypeComposite {
    private:
        Identifier* identifier_ = nullptr;
        Declarable* declarable_type_ = nullptr;
        bool built_in_ = false;
    public:

        /**
         * Set identifier
         * @param identifier
         */
        void setIdentifier(golite::Identifier* identifier) { identifier_ = identifier; }

        /**
         * Get identifier
         * @return identifier
         */
        Identifier* getIdentifier() const { return identifier_;}

        /**
         * @see TypeComposite::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see TypeComposite::toGoLiteMin()
         */
        std::string toGoLiteMin();

        /**
         * @see TyoeComposite::getLine()
         */
        int getLine();

        /**
         * @see TypeComposite::weedingPass()
         */
        void weedingPass();

        /**
         * @see TypeComposite::isTypeReference()
         */
        bool isTypeReference() { return true; }

        /**
         * @see TypeComposite::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * Get declarable type
         * @return declarable type
         */
        Declarable* getDeclarableType() const { return declarable_type_; }

        /**
         * Set declarable type
         * @param declarable_type
         */
        void setDeclarableType(Declarable* declarable_type) { declarable_type_ = declarable_type; }

        /**
         * @see TypeComposite::isCompatible()
         */
        bool isCompatible(TypeComposite* type_composite);

        /**
         * @see TypeComposite::toPrettySymbol()
         */
        std::string toPrettySymbol();

        /**
         * Set built-in value
         * @param built_in
         */
        void setBuiltIn(bool built_in) { built_in_ = built_in;}

        /**
         * Check if type reference resolves to a declarable
         * @param declarable
         * @return true if it is
         */
        bool resolvesTo(Declarable* declarable);

        /**
         * @see TypeComposite::resolveChildren()
         */
        std::vector<golite::TypeComposite*> resolveChildren();
    };
}

#endif