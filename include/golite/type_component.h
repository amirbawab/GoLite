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

        /**
         * Check if it's a bool
         * @return true if it is
         */
        bool isBool();

        /**
         * Check if it's an int
         * @return true if it is
         */
        bool isInt();

        /**
         * Check if it's a float64
         * @return true if it is
         */
        bool isFloat64();

        /**
         * Check if it's a string
         * @return true if it is
         */
        bool isString();

        /**
         * Check if it's a rune
         * @return true if it is
         */
        bool isRune();

        /**
         * Check if it's an infer
         * @return true if it is
         */
        bool isInfer();

        /**
         * Check if it's a void
         * @return true if it is
         */
        bool isVoid();

        /**
         * Check if it's comparable
         * @return true if it is
         */
        bool isComparable();

        /**
         * Check if it's ordered
         * @return true if it is
         */
        bool isOrdered();

        /**
         * Check if it's numeric
         * @return true if it is
         */
        bool isNumeric();

        /**
         * Prettify type component for symbol table
         * @return string
         */
        std::string toPrettySymbol();
    };
}

#endif