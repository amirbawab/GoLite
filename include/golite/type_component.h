#ifndef GOLITE_TYPE_COMPONENT_H
#define GOLITE_TYPE_COMPONENT_H

#include <string>
#include <vector>

namespace golite {
    class TypeComponent {
    private:
        std::vector<golite::TypeComponent*> children_;

    public:

        /**
         * Convert to GoLite code
         * @param indent
         * @return golite code
         */
        virtual std::string toGoLite(int indent);

        /**
         * Add child
         * @param type_component
         */
        void addChild(golite::TypeComponent* type_component);
    };
}

#endif