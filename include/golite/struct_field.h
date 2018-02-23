#ifndef GOLITE_STRUCT_FIELD_H
#define GOLITE_STRUCT_FIELD_H

#include <vector>
#include <string>
#include <golite/type_component.h>

namespace golite {
    class StructField {
    private:
        std::vector<std::string> names_;
        TypeComponent* type_component_;
    public:

        /**
         * Get names
         * @return names
         */
        std::vector<std::string> getNames() { return name_; }

        /**
         * Add name
         * @param name
         */
        void addName(std::string name);

        /**
         * Set type component
         * @param type_component
         */
        void setTypeComponent(TypeComponent* type_component) { type_component_ = type_component; }

        /**
         * Get type component
         * @return type component
         */
        TypeComponent* getTypeComponent() const { return type_component_; }
    };
}

#endif
