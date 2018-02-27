#ifndef GOLITE_TYPE_REFERENCE_H
#define GOLITE_TYPE_REFERENCE_H

#include <golite/type_composite.h>
#include <golite/type.h>

namespace golite {
    class TypeReference : public TypeComposite {
    private:
        Identifier* identifier_;
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
    };
}

#endif