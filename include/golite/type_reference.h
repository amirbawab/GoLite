#ifndef GOLITE_TYPE_REFERENCE_H
#define GOLITE_TYPE_REFERENCE_H

#include <golite/type_component.h>
#include <golite/type.h>

namespace golite {
    class TypeReference : public TypeComponent {
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
         * @see TypeComponent::toGoLite(int)
         */
        std::string toGoLite(int indent);
    };
}

#endif