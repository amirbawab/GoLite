#include <golite/block.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/expression.h>

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
        if(statement->isExpression()) {
            golite::Expression* expression = static_cast<Expression*>(statement);
            if(!expression->isFunctionCall()) {
                golite::Utils::error_message("Expression statement must be a function call", statement->getLine());
            }
        }
        statement->weedingPass(check_break, check_continue);
    }
}

void golite::Block::symbolTablePass(SymbolTable *root) {
    for(Statement* statement : statements_) {
        statement->symbolTablePass(root);
    }
}