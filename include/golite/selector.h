#ifndef GOLITE_SELECTOR_H
#define GOLITE_SELECTOR_H

#include <golite/primary.h>
#include <golite/identifier.h>

namespace golite {
    class Selector : public Primary {
    private:
        Identifier* identifier_ = nullptr;
    public:
        Selector(Identifier* identifier) : identifier_(identifier) {}

        /**
         * Set identifier
         * @param identifier
         */
        void setIdentifier(Identifier* identifier) { identifier_ = identifier; }

        /**
         * Get identifier
         * @return identifier
         */
        Identifier* getIdentifier() const { return identifier_; }

        /**
         * @see Expression::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * Get line number
         * @return line number
         */
        int getLine();

        /**
         * @see Expression::weedingPass()
         */
        void weedingPass();

        /**
         * @see Expression::typeCheck()
         */
        golite::TypeComponent* typeCheck();

        /**
         * @see Expression::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * @see Primary::isSelector()
         */
        bool isSelector() { return true; }
    };
}

#endif