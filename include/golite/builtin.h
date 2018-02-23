#ifndef GOLITE_STATEMENTS_DECLARABLES_BUILTIN_H
#define GOLITE_STATEMENTS_DECLARABLES_BUILTIN_H

#include <golite/type.h>
#include <golite/function.h>

namespace golite {
    class BuiltIn {
    public:
        // built-in types
        static Type* const INT_TYPE;
        static Type* const FLOAT_TYPE;
        static Type* const BOOL_TYPE;
        static Type* const RUNE_TYPE;
        static Type* const STRING_TYPE;

        // built-in functions
        static Function* const APPEND_FN;
    };
}

#endif
