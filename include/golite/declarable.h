#ifndef GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H
#define GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H

#include <golite/statement.h>
#include <string>

namespace golite {
    class Declarable : Statement {
    protected:
        Declarable(std::string name) { this->name_ = name; }
        std::string name_;
    };
}

#endif
