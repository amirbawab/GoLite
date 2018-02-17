#ifndef GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H
#define GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H

#include <golite/statements/statement.h>
#include <string>

namespace golite {
    class Declarable : Statement {
    protected:
        std::string name_;
    };
}

#endif