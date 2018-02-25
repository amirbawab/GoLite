#ifndef GOLITE_TYPE_REFERENCE_H
#define GOLITE_TYPE_REFERENCE_H

#include <golite/type_component.h>
#include <golite/type.h>

namespace golite {
    class TypeReference : public TypeComponent {
    private:
        Identifier* identifier_;
        Type* type_;
    public:

        /**
         * Set type
         * @param type
         */
        void setType(Type* type) { type_ = type; }

        /**
         * Get type
         * @return type
         */
        Type* getType() const { return type_; }

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