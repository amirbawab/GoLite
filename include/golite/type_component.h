#ifndef GOLITE_TYPE_COMPONENT_H
#define GOLITE_TYPE_COMPONENT_H

#include <string>
#include <vector>
#include <golite/type_composite.h>

namespace golite {
    class TypeComponent {
    private:
        std::vector<golite::TypeComposite*> children_;

    public:

        /**
         * Convert to GoLite code
         * @param indent
         * @return golite code
         */
        std::string toGoLite(int indent);

        /**
         * Convert to GoLite code
         * @return golite code
         */
        std::string toGoLiteMin();

        /**
         * Add child
         * @param type_composite
         */
        void addChild(golite::TypeComposite* type_composite);

        /**
         * Get line number
         * @return line number
         */
        int getLine();

        /**
         * Perform a weeding pass
         */
        void weedingPass();

        /**
         * Get children vector
         * @return children vector
         */
        std::vector<golite::TypeComposite*> getChildren() { return children_; }

        /**
         * Check if a type component is comaptible with this
         * @param type_component
         * @return true if they are compatible
         */
        bool isCompatible(TypeComponent* type_component);

        /**
         * Perform symbol table check
         * @param root
         */
        void symbolTablePass(SymbolTable* root);
    };
}

#endif