#ifndef GOLITE_TYPE_COMPOSITE_H
#define GOLITE_TYPE_COMPOSITE_H

#include <string>
#include <vector>

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
         * Check if type is int
         * @return true if it is
         */
        virtual bool isInt() { return false; }

        /**
         * Check if type is float
         * @return true if it is
         */
        virtual bool isFloat64() { return false; }

        /**
         * Check if type is boolean
         * @return true if it is
         */
        virtual bool isBool() { return false; }

        /**
         * Check if type is string
         * @return true if it is
         */
        virtual bool isString() { return false; }

        /**
         * Check if type is rune
         * @return true if it is
         */
        virtual bool isRune() { return false; }
    };
}

#endif