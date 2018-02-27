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
        virtual std::string toGoLite(int indent);

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
    };
}

#endif