#define GOLITE_SYMBOL_TABLE
#define GOLITE_SYMBOL_TABLE

#include <map>
#include <string>
#include <statements/declarables/declarable.h>

using namespace std;

namespace Golite {
    class SymbolTable {
    protected:
        SymbolTable* parent_;
        map<string, Statement::Declarable::Declarable*> entries_;
    };
}

#endif