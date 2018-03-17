#ifndef GOLITE_FUNC_H
#define GOLITE_FUNC_H

#include <golite/type_component.h>
#include <golite/function.h>

namespace golite {
    class Func : public TypeComposite {
    protected:
        golite::TypeComponent* type_component_;
        golite::Function* function_;
    public:
        Func(Function* function, golite::TypeComponent* type_component) :
                function_(function), type_component_(type_component) {}

        /**
         * Get type component
         * @return type component
         */
        golite::TypeComponent* getTypeComponent() const { return type_component_; }

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
        int getLine();

        /**
         * @see TypeComposite::weedingPass()
         */
        void weedingPass();

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
         * @see TypeComposite::isFunc()
         */
        bool isFunc() { return true; }

        /**
         * Get function
         * @return function
         */
        Function* getFunction() const { return function_; }
    };
}

#endif
