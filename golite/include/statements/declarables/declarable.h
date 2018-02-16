#ifndef GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H
#define GOLITE_STATEMENTS_DECLARABLES_DECLARABLE_H

#include <statements/statement.h>
#include <string>

namespace Golite::Statement::Declarable {
    class Declarable : Statement {
    protected:
        std::string name_;
    };
}

#endif