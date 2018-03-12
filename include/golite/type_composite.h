#ifndef GOLITE_TYPE_COMPOSITE_H
#define GOLITE_TYPE_COMPOSITE_H

#include <string>
#include <vector>
#include <golite/symbol_table.h>

namespace golite {
    class TypeComposite {
    public:

        /**
         * Convert to GoLite code
         * @param indent
         * @return golite code
         */
        virtual std::string toGoLite(int indent) = 0;

        /**
         * Convert to GoLite min code
         * @return golite code
         */
        virtual std::string toGoLiteMin() = 0;

        /**
         * Get line number
         * @return line number
         */
        virtual int getLine() = 0;

        /**
         * Perform a weeding pass
         */
        virtual void weedingPass() = 0;

        /**
         * Struct types return true
         * @return true for struct
         */
        virtual bool isStruct() { return false; }

        /**
         * Reference types return true
         * @return true for reference type
         */
        virtual bool isTypeReference() { return false; }

        /**
         * Array types return true
         * @return true for array
         */
        virtual bool isArray() { return false; }

        /**
         * Slice types return true
         * @return true for slice
         */
        virtual bool isSlice() { return false; }

        /**
         * Perform symbol table check
         * @param root
         */
        virtual void symbolTablePass(SymbolTable* root) = 0;

        /**
         * Check if elements are compatible
         * @return true if they are
         */
        virtual bool isCompatible(TypeComposite* type_composite) = 0;

        /**
         * Display output in symbol table format
         * @return string
         */
        virtual std::string toPrettySymbol() = 0;

        /**
         * Check if type composite resolves an element
         * @param declarable
         * @return true if it does
         */
        virtual bool resolvesTo(Declarable* declarable) { return false; }

        /**
         * Resolve children
         * @return children
         */
        virtual std::vector<TypeComposite*> resolveChildren(bool recursive = true) = 0;
    };
}

#endif