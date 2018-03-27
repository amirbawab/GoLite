#ifndef GOLITE_FUNCTION_PARAM_H
#define GOLITE_FUNCTION_PARAM_H

#include <string>
#include <vector>
#include <golite/type_component.h>
#include <golite/identifier.h>

namespace golite {
    class FunctionParam {
    private:
        std::vector<Identifier*> identifiers_;
        TypeComponent* type_component_ = nullptr;
    public:

        /**
         * Set identifiers
         * @param identifier
         */
        void setIdentifiers(std::vector<Identifier*> identifiers) { identifiers_ = identifiers; }

        /**
         * Get identifiers
         * @return identifiers
         */
        std::vector<Identifier*> getIdentifier() { return identifiers_; }

        /**
         * Set type component
         * @param type_component
         */
        void setTypeComponent(golite::TypeComponent* type_component) { type_component_ = type_component; }

        /**
         * Get type component
         * @return type component
         */
        TypeComponent* getTypeComponent() const { return type_component_; }

        /**
         * Conver to GoLite code
         * @param indent
         * @return golite code
         */
        std::string toGoLite(int indent);

        /**
         * Perform a weeding pass
         */
        void weedingPass();

        /**
         * Perform symbol table check
         * @param root
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * To type script
         * @param indent
         * @return code
         */
        std::string toTypeScript(int indent);

        /**
         * To type script initializer
         * @param indent
         * @return code
         */
        std::string toTypeScriptInitializer(int indent);
    };
}

#endif
