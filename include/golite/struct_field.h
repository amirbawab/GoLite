#ifndef GOLITE_STRUCT_FIELD_H
#define GOLITE_STRUCT_FIELD_H

#include <string>
#include <vector>
#include <golite/type_component.h>
#include <golite/identifier.h>

namespace golite {
    class StructField {
    private:
        std::vector<Identifier*> identifiers_;
        TypeComponent* type_component_ = nullptr;
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

        /**
         * Conver to GoLite
         * @param indent
         * @return golite code
         */
        std::string toGoLite(int indent);

        /**
         * Conver to GoLite min
         * @return golite code
         */
        std::string toGoLiteMin();

        /**
         * Perform a weeding pass
         */
        virtual void weedingPass();

        /**
         * Perform symbol table check
         * @param root
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * Get identifiers
         * @return identifiers
         */
        std::vector<golite::Identifier*> getIdentifiers() { return identifiers_; }

        /**
         * Get type component
         * @return type component
         */
        TypeComponent* getTypeComponent() { return type_component_; }

        /**
         * Check if struct field is recursive
         * @param type
         * @return true if it is
         */
        bool isRecursive(Type* type);

        /**
         * Convert to type script
         * @param indent
         * @return code
         */
        std::string toTypeScript(int indent);
    };
}

#endif
