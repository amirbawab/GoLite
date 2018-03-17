#include <golite/symbol_table.h>
#include <golite/declarable.h>
#include <golite/utils.h>
#include <iostream>
#include <golite/program.h>

golite::SymbolTable::SymbolTable(SymbolTable *parent) {
    parent_ = parent;
    if(parent) {
        parent->putTable(this);
    }
}

void golite::SymbolTable::putSymbol(std::string name, golite::Declarable *decl) {
    if(entries_.find(name) != entries_.end()) {
        throw std::runtime_error("Identifier " + name + " already exists in the symbol table");
    }

    // If program scope
    if(this == Program::getInstance()->getProgramSymbolTable()) {
        if(!decl->isFunction()) {
            if(name == Program::INIT_FUNC_NAME || name == Program::MAIN_FUNC_NAME) {
                golite::Utils::error_message("Variable " + name + " must be a function", decl->getLine());
            }
        }
    }
    this->entries_[name] = decl;
    this->entries_keys_.push_back(name);
}

void golite::SymbolTable::putInit(Declarable *decl) {
    std::string init_name = init_prefix + std::to_string(entries_keys_.size());
    putSymbol(init_name, decl);
}

void golite::SymbolTable::putTable(SymbolTable *table) {
    std::string unique_key = " ~ " + std::to_string(entries_keys_.size()) + " ~ ";
    tables_[unique_key] = table;
    entries_keys_.push_back(unique_key);
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

std::string golite::SymbolTable::toPrettySymbol(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "{" << std::endl;
    indent++;

    // show entries
    for(std::string key : entries_keys_) {
        if(entries_.find(key) != entries_.end()) {
            if(entries_[key]->isDecVariable()) {
                ss << golite::Utils::indent(indent) << key << entries_[key]->toPrettySymbol() << std::endl;
            } else {
                ss << golite::Utils::indent(indent) << entries_[key]->toPrettySymbol() << std::endl;
            }
        }

        if(tables_.find(key) != tables_.end()) {
            ss << tables_[key]->toPrettySymbol(indent);
        }
    }

    indent--;
    ss << golite::Utils::indent(indent) << "}" << std::endl;
    return ss.str();
}