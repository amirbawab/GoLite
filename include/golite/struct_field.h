#ifndef GOLITE_STRUCT_FIELD_H
#define GOLITE_STRUCT_FIELD_H

#include <vector>
#include <golite/type_component.h>
#include <golite/identifier.h>

namespace golite {
    class StructField {
    private:
        std::vector<Identifier*> identifiers_;
        TypeComponent* type_component_;
    public:

        /**
         * Set identifiers
         * @param identifiers
         */
        void setIdentifiers(std::vector<golite::Identifier*> identifiers) { identifiers_ = identifiers; }

        /**
         * Set type component
         * @param type_component
         */
        void setTypeComponent(golite::TypeComponent* type_component) { type_component_ = type_component; }
    };
}

#endif
