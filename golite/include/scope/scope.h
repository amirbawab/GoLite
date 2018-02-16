#ifndef GOLITE_SCOPE_SCOPE_H
#define GOLITE_SCOPE_SCOPE_H

#include <vector>
#include <statements/statement.h>
#include <symbol_table.h>

using namespace std;
using namespace Golite;

namespace Golite::Scope {
    class Scope {
    protected:
        vector<Statement::Statement*>* statements_;
        SymbolTable symbol_table_;
    };
}

#endif