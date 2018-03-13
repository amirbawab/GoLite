#include <golite/block.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/simple_expression.h>

std::string golite::Block::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "{";
    if(!statements_.empty()) {
        ss << std::endl;
        for(Statement* statement : statements_) {
            ss << statement->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}

void golite::Block::weedingPass(bool check_break, bool check_continue) {
    for(Statement* statement : statements_) {
        statement->weedingPass(check_break, check_continue);
    }
}

void golite::Block::typeCheck() {
    for (Statement *statement : statements_) {
        statement->typeCheck();
    }
}

void golite::Block::symbolTablePass(SymbolTable *root) {
    for(Statement* statement : statements_) {
        SymbolTable* block_table = root;
        if(statement->isBlock()) {
            block_table = new SymbolTable(root);
        }
        statement->symbolTablePass(block_table);
    }
}

bool golite::Block::hasReturn(Declarable* function) {
    bool has_return = false;
    for(Statement* statement : statements_) {
        has_return |= statement->hasReturn(function);
    }
    return has_return;
}

bool golite::Block::hasBreak() {
    for(Statement* statement : statements_) {
        // Don't check for and switch statements
        // because if they a break then it's for them
        // and not for the current block
        if(!statement->isFor() && !statement->isSwitch() && statement->hasBreak()) {
            return true;
        }
    }
    return false;
}