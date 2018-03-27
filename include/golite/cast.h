#ifndef GOLITE_CAST_H
#define GOLITE_CAST_H

#include <golite/pointer.h>
#include <golite/type.h>

namespace golite {
    class Cast : public Pointer {
    private:
        int line_;
        Type* type_ = nullptr;
    public:
        Cast(int line, Type* type) : line_(line), type_(type) {}

        /**
         * @see TypeComposite::getTypeComponent()
         */
        golite::TypeComponent* getTypeComponent();

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
         * @see TypeComposite::isCast()
         */
        bool isCast() { return true; }

        /**
         * Get type
         * @return type
         */
        Type* getType() const { return type_; }

        /**
         * @see TypeComposite::toTypeScript()
         */
        std::string toTypeScript(int indent);

        /**
         * @see TypeComposite::toTypeScriptInitializer()
         */
        std::string toTypeScriptInitializer(int indent);
    };
}

#endif
