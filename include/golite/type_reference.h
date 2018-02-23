#ifndef GOLITE_TYPE_REFERENCE_H
#define GOLITE_TYPE_REFERENCE_H

#include <golite/type_component.h>
#include <golite/type.h>

namespace golite {
    class TypeReference : public TypeComponent {
    private:
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
    };
}

#endif