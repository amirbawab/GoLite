#include <golite/for.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/primary_expression.h>
#include <golite/identifier.h>

std::string golite::For::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "for ";
    if(left_simple_ || right_simple_) {
        if(left_simple_) {
            ss << left_simple_->toGoLite(0);
        }
        ss << "; ";

        if(expression_) {
            ss << expression_->toGoLite(0);
        }
        ss << "; ";

        if(right_simple_) {
            ss << right_simple_->toGoLite(0) << " ";
        }
    } else if(expression_) {
        ss << expression_->toGoLite(0) << " ";
    }
    ss << "{";
    if(!block_->getStatements().empty()) {
        ss << std::endl;
        for(Statement* statement : block_->getStatements()) {
            ss << statement->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}

void golite::For::weedingPass(bool, bool) {
    if(left_simple_) {
        if(left_simple_->isExpression()) {
            golite::Expression* expression = static_cast<Expression*>(left_simple_);
            if(expression->isBlank()) {
                golite::Utils::error_message("For statement pre statement cannot be a blank identifier",
                                             left_simple_->getLine());
            }
        }
        left_simple_->weedingPass(false, false);
    }

    if(expression_) {
        if(expression_->isBlank()) {
            golite::Utils::error_message("For statement expression cannot be a blank identifier",
                                         expression_->getLine());
        }
        expression_->weedingPass(false, false);
    }

    if(right_simple_) {
        if(right_simple_->isExpression()) {
            golite::Expression* expression = static_cast<Expression*>(right_simple_);
            if(expression->isBlank()) {
                golite::Utils::error_message("For statement post statement cannot be a blank identifier",
                                             right_simple_->getLine());
            }
        }
        right_simple_->weedingPass(false, false);
    }
    block_->weedingPass(false, false);
}

void golite::For::symbolTablePass(SymbolTable *root) {
    golite::SymbolTable* for_symbol_table = new golite::SymbolTable();
    root->addChild(for_symbol_table);

    this->left_simple_->symbolTablePass(for_symbol_table);
    this->right_simple_->symbolTablePass(for_symbol_table);

    this->block_->symbolTablePass(for_symbol_table);
}