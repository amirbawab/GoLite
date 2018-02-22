#ifndef GOLITE_STATEMENTS_DECLARABLES_BUILTIN_H
#define GOLITE_STATEMENTS_DECLARABLES_BUILTIN_H

#include <golite/expressions/identifier_expression.h>
#include <golite/statements/declarables/type_declarable.h>
#include <golite/statements/declarables/function_declarable.h>

namespace golite {
    class BuiltIn {
    public:
        // built-in types
        static TypeDeclarable* const INT_TYPE;
        static TypeDeclarable* const FLOAT_TYPE;
        static TypeDeclarable* const BOOL_TYPE;
        static TypeDeclarable* const RUNE_TYPE;
        static TypeDeclarable* const STRING_TYPE;

        // built-in functions
        static IdentifierExpression* const APPEND_FN_ID;
        static FunctionDeclarable* const APPEND_FN;
    };
}

#endif