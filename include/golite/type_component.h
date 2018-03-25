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
        TypeComponent() {}
        TypeComponent(std::vector<TypeComposite*> children) : children_(children){}

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
         * Resolve children recursively
         * @return vector
         */
        std::vector<golite::TypeComposite*> resolveChildren();

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
         * Check if it resolves to a type
         * @return true if it does
         */
        bool resolvesTo(Declarable* declarable_type);

        /**
         * Check if it's an int
         * @return true if it is
         */
        bool isInt();

        /**
         * Check if it's an int or rune
         * @return true if it is
         */
        bool isInteger();

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

        /**
         * Check if type component is recursive
         * @param type
         * @return true if it is
         */
        bool isRecursive(Type* type);

        /**
         * Check if resolves to bools
         * @return true if it does
         */
        bool resolvesToBool();

        /**
         * Check if resolves to float
         * @return true if it does
         */
        bool resolvesToFloat64();

        /**
         * Check if resolves to int
         * @return true if it does
         */
        bool resolvesToInt();

        /**
         * Check if resolves to int or rune
         * @return true if it does
         */
        bool resolvesToInteger();

/**
         * Check if resolves to string
         * @return true if it does
         */
        bool resolvesToString();
        /**
         * Check if resolves to rune
         * @return true if it does
         */
        bool resolvesToRune();

        /**
         * Check if it's comparable
         * @return true if it is
         */
        bool resolvesToComparable();

        /**
         * Check if it's ordered
         * @return true if it is
         */
        bool resolvesToOrdered();

        /**
         * Check if it's numeric
         * @return true if it is
         */
        bool resolvesToNumeric();

        /**
         * Check if is base type
         * @return true if it is
         */
        bool isBaseType();

        /**
         * Check if resolves to base type
         * @return true if it does
         */
        bool resolvesToBaseType();

        /**
         * Resolve type component of a function
         * @return resolve type component of func
         */
        golite::TypeComponent* resolveFunc();

        /**
         * Check if type component has a pointer
         * @return pointer
         */
        bool isPointer();

        /**
         * Check if type component has a func
         * @return pointer
         */
        bool isFunc();

/**
         * Check if type component has a cast
         * @return pointer
         */
        bool isCast();

        /**
         * Generate typescript code
         * @return code
         */
        std::string toTypeScript(int indent);

        /**
         * Generate typescript code
         * @return code
         */
        std::string toTypeScriptInitializer(int indent);

        /**
         * Generate default type code expression value
         * @return string
         */
        std::string toTypeScriptDefaultValue();

        /**
         * Check if is array
         * @return true if it is
         */
        bool isArray();

        /**
         * Check if is slice
         * @return true if it is
         */
        bool isSlice();

        /**
         * Check if is struct
         * @return true if it is
         */
        bool isStruct();

        /**
         * Check if is type reference
         * @return true if it is
         */
        bool isTypeReference();
    };
}

#endif