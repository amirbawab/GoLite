#ifndef GOLITE_STATEMENTS_IF_H
#define GOLITE_STATEMENTS_IF_H

#include <golite/statement.h>
#include <golite/block.h>
#include <golite/expression.h>

namespace golite {

    /**
     * If statement with optional else if and else statements
     */
    class IfStatement : Statement {
    protected:
        Expression* expression_;
        // FIXME Update Scope to block
        Scope* block_;
        std::vector<IfStatement*> else_if_;
        Scope* else_;
        SimpleStatement simple_
    };
}

#endif
