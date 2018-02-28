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

void golite::For::weedingPass(bool check_break, bool check_continue) {
    if(left_simple_) {
        if(left_simple_->isExpression()) {
            golite::Expression* expression = static_cast<Expression*>(left_simple_);
            golite::PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(expression);
            golite::Identifier* identifier = static_cast<Identifier*>(primary_expression->lastChild());
            if(identifier->isBlank()) {
                golite::Utils::error_message("For statement pre statement cannot be a blank identifier",
                                             left_simple_->getLine());
            }
        }
        left_simple_->weedingPass(check_break, check_continue);
    }

    if(expression_) {
        golite::PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(expression_);
        golite::Identifier* identifier = static_cast<Identifier*>(primary_expression->lastChild());
        if(identifier->isBlank()) {
            golite::Utils::error_message("For statement expression cannot be a blank identifier",
                                         expression_->getLine());
        }
        expression_->weedingPass(check_break, check_continue);
    }

    if(right_simple_) {
        if(right_simple_->isExpression()) {
            golite::Expression* expression = static_cast<Expression*>(right_simple_);
            golite::PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(expression);
            golite::Identifier* identifier = static_cast<Identifier*>(primary_expression->lastChild());
            if(identifier->isBlank()) {
                golite::Utils::error_message("For statement post statement cannot be a blank identifier",
                                             right_simple_->getLine());
            }
        }
        right_simple_->weedingPass(check_break, check_continue);
    }
    block_->weedingPass(false, false);
}