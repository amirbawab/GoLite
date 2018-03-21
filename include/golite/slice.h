#ifndef GOLITE_SLICE_H
#define GOLITE_SLICE_H

#include <golite/type_composite.h>

namespace golite {
    class Slice : public TypeComposite {
    private:
        int line_;
    public:
        Slice(int line) : line_(line) {}

        /**
         * @see TypeComposite::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see TypeComponent::toGotLiteMin()
         */
        std::string toGoLiteMin();

        /**
         * @see TypeComposite::getLine()
         */
        int getLine() { return line_; }

        /**
         * @see TypeComposite::weedingPass()
         */
        void weedingPass();

        /**
         * @see TypeComposite::isSlice()
         */
        bool isSlice() { return true; }

        /**
         * @see TypeComposite::symbolTablePass()
         */
        void symbolTablePass(SymbolTable* root);

        /**
         * @see TypeComposite::isCompatible()
         */
        bool isCompatible(TypeComposite* type_composite);

        /**
         * @see TypeComposite::toPrettySymbol()
         */
        std::string toPrettySymbol();

        /**
         * @see TypeComposite::resolveChildren()
         */
        std::vector<golite::TypeComposite*> resolveChildren();

        /**
         * @see TypeComposite::isComparable()
         */
        bool isComparable() { return false; }

        /**
         * @see TypeComposite::resolvesToComparable()
         */
        bool resolvesToComparable() { return false; }

        /**
         * @see TypeComposite::isRecursive()
         */
        bool isRecursive(Type* type) { return false; }

        /**
         * @see TypeComposite::toTypeScript()
         */
        std::string toTypeScript(int indent);
    };
}

#endif