#include <golite/scope/scope.h>

using namespace std;
using namespace golite;

Scope::Scope() {
    this->statements_ = new vector<Statement*>();
    this->symbol_table_ = SymbolTable();
}
