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
        if(simple_->isSimpleExpression()) {
            golite::SimpleExpression* simple_expression = static_cast<SimpleExpression*>(simple_);
            if(simple_expression->getExpression()->isBlank()) {
                golite::Utils::error_message("If statement initial statement cannot be a blank identifier",
                                             simple_->getLine());
            }
        }
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
    symbol_table_ = new SymbolTable();
    root->addChild(symbol_table_);

    if(this->simple_) {
        this->simple_->symbolTablePass(symbol_table_);
    }
    this->expression_->symbolTablePass(symbol_table_);
    this->block_->symbolTablePass(symbol_table_);

    for(golite::If* else_if_stmt : this->else_if_) {
        else_if_stmt->symbolTablePass(symbol_table_);
    }

    if(this->else_) {
        this->else_->symbolTablePass(symbol_table_);
    }
}

bool golite::If::hasReturn(Declarable* function) {
    bool has_return = true;
    has_return &= block_->hasReturn(function);

    for(If* else_if_stmt : else_if_) {
        has_return &= else_if_stmt->hasReturn(function);
    }

    if(else_) {
        has_return &= else_->hasReturn(function);
    } else {
        has_return = false;
    }
    return has_return;
}