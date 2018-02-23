#ifndef GOLITE_EXPRESSIONS_EXPRESSION_H
#define GOLITE_EXPRESSIONS_EXPRESSION_H

#include <golite/simple.h>

namespace golite {
    /**
     * Parent class for all kind of expressions
     * - Primary
     * - Unary
     * - Binary
     * - Append (GoLite extra feature)
     */
    class Expression : public Simple {

    };
}

#endif