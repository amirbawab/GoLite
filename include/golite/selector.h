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
         * @see Statement::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * Get line number
         * @return line number
         */
        int getLine();
    };
}

#endif