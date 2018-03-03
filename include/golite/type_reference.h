#ifndef GOLITE_TYPE_REFERENCE_H
#define GOLITE_TYPE_REFERENCE_H

#include <golite/type_composite.h>
#include <golite/type.h>

namespace golite {
    class TypeReference : public TypeComposite {
    private:
        Identifier* identifier_ = nullptr;
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
         * Check if type is int
         * @return true if it is
         */
        bool isInt();

        /**
         * Check if type is float
         * @return true if it is
         */
        bool isFloat64();

        /**
         * Check if type is boolean
         * @return true if it is
         */
        bool isBool();

        /**
         * Check if type is string
         * @return true if it is
         */
        bool isString();

        /**
         * Check if type is rune
         * @return true if it is
         */
        bool isRune();
    };
}

#endif