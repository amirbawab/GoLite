#ifndef GOLITE_EXPRESSIONS_IDENTIFIER_H
#define GOLITE_EXPRESSIONS_IDENTIFIER_H

#include <string>
#include <utility>
#include <golite/expression.h>

namespace golite {
    // FIXME Update inheritance
    class IdentifierExpression : public Expression {
    public:
        IdentifierExpression(std::string name, int line): Expression(line) {
            this->name_ = name;
        }

        std::string getName() { return this->name_; }
    protected:
        std::string name_;
    };
}

#endif
