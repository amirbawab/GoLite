#include <golite/if.h>
#include <golite/utils.h>
#include <sstream>
#include <iostream>
#include <golite/primary_expression.h>
#include <golite/identifier.h>
#include <golite/simple_expression.h>
#include <golite/program.h>

std::string golite::If::toGoLite(int indent) {
    std::stringstream ss;

    // If statement
    ss << golite::Utils::indent(indent) << "if ";
    if(simple_) {
        ss << simple_->toGoLite(0) << "; ";
    }
    ss << expression_->toGoLite(0) << " {";

    // Statement body
    if(!block_->getStatements().empty()) {
        ss << std::endl;
        for(Statement* statement : block_->getStatements()) {
            ss << statement->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";

    // Else if statements
    for(If* else_if : else_if_) {

        ss << " else if ";
        if(else_if->simple_) {
            ss << else_if->simple_->toGoLite(0) << "; ";
        }
        ss << else_if->expression_->toGoLite(0) << " {";

        // Statement body
        if(!else_if->block_->getStatements().empty()) {
            ss << std::endl;
            for(Statement* statement : else_if->block_->getStatements()) {
                ss << statement->toGoLite(indent+1) << std::endl;
            }
            ss << golite::Utils::indent(indent);
        }
        ss << "}";
    }

    // Else statement
    if(else_) {
        ss << " else {";
        if(!else_->getStatements().empty()) {
            ss << std::endl;
            for(Statement* statement : else_->getStatements()) {
                ss << statement->toGoLite(indent+1) << std::endl;
            }
            ss << golite::Utils::indent(indent);
        }
        ss << "}";
    }

    return ss.str();
}

void golite::If::weedingPass(bool check_break, bool check_continue) {
    if(simple_) {
        simple_->weedingPass(false, false);
    }

    if(expression_->isBlank()) {
        golite::Utils::error_message("If statement expression cannot be a blank identifier", expression_->getLine());
    }
    expression_->weedingPass();

    for(If* else_if_stmt : else_if_) {
        else_if_stmt->weedingPass(check_break, check_continue);
    }

    if(else_) {
        else_->weedingPass(check_break, check_continue);
    }

    block_->weedingPass(check_break, check_continue);
}

void golite::If::typeCheck() {
    if (simple_) {
        simple_->typeCheck();
    }

    TypeComponent* expression_type = expression_->typeCheck();
    if (!expression_type->resolvesToBool()) {
        golite::Utils::error_message("If condition must evaluate to a bool but given " + expression_type->toGoLiteMin(),
                                     expression_->getLine());
    }
    block_->typeCheck();

    for (If *else_if : else_if_) {
        else_if->typeCheck();
    }

    if (else_) {
        else_->typeCheck();
    }
}

void golite::If::symbolTablePass(SymbolTable *root) {
    static long count = 1;
    std::string if_name_prefix = "_if_" + std::to_string(count++);
    SymbolTable* if_outer_table = new SymbolTable(root, if_name_prefix + "_o");

    if(this->simple_) {
        this->simple_->symbolTablePass(if_outer_table);
    }
    this->expression_->symbolTablePass(if_outer_table);

    SymbolTable* if_inner_table = new SymbolTable(if_outer_table, if_name_prefix + "_i");
    this->block_->symbolTablePass(if_inner_table);

    SymbolTable* prev_else_if_outer = if_outer_table;
    for(golite::If* else_if_stmt : this->else_if_) {
        std::string else_if_name_prefix = "_else_if_" + std::to_string(count++);
        SymbolTable* else_if_outer_table = new SymbolTable(prev_else_if_outer, else_if_name_prefix + "_o");

        if(else_if_stmt->simple_) {
            else_if_stmt->simple_->symbolTablePass(else_if_outer_table);
        }
        else_if_stmt->expression_->symbolTablePass(else_if_outer_table);

        SymbolTable* else_if_inner_table = new SymbolTable(else_if_outer_table, else_if_name_prefix + "_i");
        else_if_stmt->block_->symbolTablePass(else_if_inner_table);
        prev_else_if_outer = else_if_outer_table;
    }

    if(this->else_) {
        SymbolTable* else_inner_table = new SymbolTable(prev_else_if_outer, "_else_" + std::to_string(count++));
        this->else_->symbolTablePass(else_inner_table);
    }
}

void golite::If::checkReturn(Declarable* function) {
    block_->checkReturn(function);

    for(If* else_if_stmt : else_if_) {
        else_if_stmt->checkReturn(function);
    }

    if(else_) {
        else_->checkReturn(function);
    }
}

bool golite::If::hasBreak() {
    return block_->hasBreak();
}

bool golite::If::isTerminating() {
    bool is_terminating = true;
    is_terminating &= block_->isTerminating();

    for(If* else_if_stmt : else_if_) {
        is_terminating &= else_if_stmt->block_->isTerminating();
    }

    if(else_) {
        is_terminating &= else_->isTerminating();
    } else {
        is_terminating = false;
    }

    if(!is_terminating) {
        golite::Utils::error_message("If statement is not terminating in all branches", getLine());
    }
    return true;
}

std::string golite::If::toTypeScript(int indent) {
    std::stringstream ss;
    if(simple_) {
        ss << simple_->toTypeScript(indent) << std::endl;
    }
    for(If* else_if : else_if_) {
        if(else_if->simple_) {
            ss << else_if->simple_->toTypeScript(indent) << std::endl;
        }
    }
    ss << golite::Utils::blockComment({"If statement"}, indent, getLine()) << std::endl
       << golite::Utils::indent(indent) << "if(" << expression_->toTypeScript(0) << ") {";
    if(!block_->getStatements().empty()) {
        ss << std::endl;
        for(Statement* statement : block_->getStatements()) {
            ss << statement->toTypeScript(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";
    for(If* else_if : else_if_) {
        ss << " else if(" << else_if->expression_->toTypeScript(0) << ") {";
        if(!else_if->block_->getStatements().empty()) {
            ss << std::endl;
            for(Statement* statement : else_if->block_->getStatements()) {
                ss << statement->toTypeScript(indent+1) << std::endl;
            }
            ss << golite::Utils::indent(indent);
        }
        ss << "}";
    }
    if(else_) {
        ss << " else {";
        if(!else_->getStatements().empty()) {
            ss << std::endl;
            for(Statement* statement : else_->getStatements()) {
                ss << statement->toTypeScript(indent+1) << std::endl;
            }
            ss << golite::Utils::indent(indent);
        }
        ss << "}";
    }
    ss << std::endl;
    return ss.str();
}