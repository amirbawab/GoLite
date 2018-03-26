#ifndef GOLITE_STRUCT_H
#define GOLITE_STRUCT_H

#include <vector>
#include <golite/type_composite.h>
#include <golite/struct_field.h>

namespace golite {
    class Struct : public TypeComposite {
    private:
        std::vector<StructField*> fields_;
        int line_;
        std::string name_;
    public:
        Struct(int line) : line_(line) {}

        /**
         * @see TypeComposite::getLine()
         */
        int getLine() { return line_; }

        /**
         * Set fields
         * @param fields
         */
        void setFields(std::vector<StructField*> fields) { fields_ = fields; }

        /**
         * @see TypeComponent::toGoLite(int)
         */
        std::string toGoLite(int indent);

        /**
         * @see TypeComposite::toGoLiteMin()
         */
        std::string toGoLiteMin();

        /**
         * @see TypeComposite::weedingPass()
         */
        void weedingPass();

        /**
         * @see TypeComposite::isStruct()
         */
        bool isStruct() { return true; }

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
         * Get field
         * @param name
         * @return field | nullptr
         */
        StructField* getField(std::string name);

        /**
         * @see TypeComposite::isComparable()
         */
        bool isComparable();

        /**
         * @see TypeComposite::resolvesToComparable()
         */
        bool resolvesToComparable();

        /**
         * @see TypeComposite::isRecursive()
         */
        bool isRecursive(Type* type);

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
