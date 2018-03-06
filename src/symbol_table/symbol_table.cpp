#include <golite/symbol_table.h>
#include <iterator>

void golite::SymbolTable::addChild(SymbolTable *table) {
    table->parent_ = this;
    this->children_.push_back(table);
}

void golite::SymbolTable::putSymbol(std::string name, golite::Symbol *decl) {
    this->entries_.insert(std::pair<std::string, golite::Symbol*>(name, decl));
    // TODO : check what to do with existing entries ? probably only need to replace
}

golite::Symbol* golite::SymbolTable::getSymbol(std::string name, bool search_in_parent) {
    SymbolTable* curr_sym_table = this;
    std::map<std::string, golite::Symbol*>::iterator found;
    while(curr_sym_table) {
        found = curr_sym_table->entries_.find(name);
        if(found != curr_sym_table->entries_.end() || !search_in_parent) { return (*found).second; }
    }

    return nullptr;
}

bool golite::SymbolTable::hasSymbol(std::string name, bool search_in_parent) {
    return this->getSymbol(name, search_in_parent) != nullptr;
}
