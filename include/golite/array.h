#ifndef GOLITE_ARRAY_H
#define GOLITE_ARRAY_H

#include <golite/type_composite.h>
#include <golite/literal.h>

namespace golite {
    class Array : public TypeComposite {
    private:
        golite::Literal<int>* size_ = nullptr;
    public:
        Array(golite::Literal<int>* size) : size_(size) {}

        /**
         * Get size
         * @return size
         */
        golite::Literal<int>* getSize() const { return size_; }

        /**
         * @see TypeComponent::toGoLite()
         */
        std::string toGoLite(int indent);

        /**
         * @see TypeComponent::toGotLiteMin()
         */
        std::string toGoLiteMin();

        /**
         * @see TypeComposite::getLine()
         */
        int getLine();

        /**
         * @see TypeComposite::weedingPass()
         */
        void weedingPass();

        /**
         * @see TypeComposite::isArray()
         */
        bool isArray() { return true; }

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
        bool isComparable() { return true; }

        /**
         * @see TypeComposite::resolvesToComparable()
         */
        bool resolvesToComparable() { return true; }

        /**
         * @see TypeComposite::isRecursive()
         */
        bool isRecursive(Type* type) { return true; }
    };
}

#endif