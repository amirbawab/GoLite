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
    };
}

#endif