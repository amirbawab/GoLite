#ifndef GOLITE_EXPRESSIONS_IDENTIFIER_H
#define GOLITE_EXPRESSIONS_IDENTIFIER_H

#include <string>
#include <expressions/expression.h>

using namespace std;

namespace Golite::Expression {
    class IdentifierExpression : Expression {
    protected:
        string name_;
    };
}

#endif