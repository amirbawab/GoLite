#include <golite/symbol_table.h>
#include <golite/declarable.h>
#include <golite/utils.h>

void golite::SymbolTable::addChild(SymbolTable *table) {
    table->parent_ = this;
    this->children_.push_back(table);
}

void golite::SymbolTable::putSymbol(std::string name, golite::Declarable *decl) {
    if(entries_.find(name) != entries_.end()) {
        throw std::runtime_error("Identifier " + name + " already exists in the symbol table");
    }
    this->entries_[name] = decl;
    this->entries_keys_.push_back(name);
}

golite::Declarable* golite::SymbolTable::getSymbol(std::string name, bool search_in_parent) {
    SymbolTable* curr_sym_table = this;
    std::map<std::string, golite::Declarable*>::iterator found;
    while(curr_sym_table) {
        found = curr_sym_table->entries_.find(name);
        if(found != curr_sym_table->entries_.end()) {
            return (*found).second;
        } else if(!search_in_parent) {
            return nullptr;
        }
        curr_sym_table = curr_sym_table->parent_;
    }
    return nullptr;
}

void golite::SymbolTable::updateSymbol(std::string name, Declarable* new_declarable, bool search_in_parent) {
    SymbolTable* curr_sym_table = this;
    std::map<std::string, golite::Declarable*>::iterator found;
    while(curr_sym_table) {
        found = curr_sym_table->entries_.find(name);
        if(found != curr_sym_table->entries_.end()) {
            found->second = new_declarable;
            return;
        } else if(!search_in_parent) {
            break;
        }
        curr_sym_table = curr_sym_table->parent_;
    }
    throw std::runtime_error("Cannot update an entry that does not exist in symbol table");
}

golite::SymbolTable* golite::SymbolTable::getSymbolTable(std::string name, bool search_in_parent) {
    SymbolTable* curr_sym_table = this;
    std::map<std::string, golite::Declarable*>::iterator found;
    while(curr_sym_table) {
        found = curr_sym_table->entries_.find(name);
        if(found != curr_sym_table->entries_.end()) {
            return curr_sym_table;
        } else if(!search_in_parent) {
            break;
        }
        curr_sym_table = curr_sym_table->parent_;
    }
    throw std::runtime_error("Cannot get symbol table of an unrecognized identifier");
}

bool golite::SymbolTable::hasSymbol(std::string name, bool search_in_parent) {
    return this->getSymbol(name, search_in_parent) != nullptr;
}

std::string golite::SymbolTable::prettyPrint(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "{" << std::endl;
    indent++;

    // show entries
    for(std::string key : entries_keys_) {
        ss << golite::Utils::indent(indent) << key << " [" << entries_[key]->toPrettySymbol() << "]" << " = " << std::endl;
    }

    // show nested symbol table
    for(SymbolTable* child : this->children_) {
        ss << child->prettyPrint(indent) << std::endl;
    }

    indent--;
    ss << golite::Utils::indent(indent) << "}" << std::endl;
    return ss.str();
}