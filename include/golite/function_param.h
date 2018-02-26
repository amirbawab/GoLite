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
        TypeComponent* type_component_;
    public:

        /**
         * Set identifiers
         * @param identifier
         */
        void setIdentifiers(std::vector<Identifier*> identifiers) { identifiers_ = identifiers; }

        /**
         * Set type component
         * @param type_component
         */
        void setTypeComponent(golite::TypeComponent* type_component) { type_component_ = type_component; }

        /**
         * Conver to GoLite code
         * @param indent
         * @return golite code
         */
        std::string toGoLite(int indent);
    };
}

#endif
