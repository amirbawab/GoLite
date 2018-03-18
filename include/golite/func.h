#ifndef GOLITE_FUNC_H
#define GOLITE_FUNC_H

#include <golite/pointer.h>
#include <golite/function.h>

namespace golite {
    class Func : public Pointer {
    private:
        golite::TypeComponent* type_component_ = nullptr;
        golite::Function* function_ = nullptr;
    public:
        Func(Function* function, golite::TypeComponent* type_component) :
                function_(function), type_component_(type_component) {}

        /**
         * @see TypeComposite::getTypeComponent()
         */
        golite::TypeComponent* getTypeComponent() { return type_component_; }

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
