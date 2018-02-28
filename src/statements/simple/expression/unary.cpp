#include <golite/unary.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>

std::string golite::Unary::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "(";
    switch (kind_) {
        case MINUS:
            ss << "-";
            break;
        case NOT:
            ss << "!";
            break;
        case PLUS:
            ss << "+";
            break;
        case XOR:
            ss << "^";
            break;
    }
    ss << operand_->toGoLite(0) << ")";
    return ss.str();
}

int golite::Unary::getLine() {
    return operand_->getLine();
}

void golite::Unary::weedingPass(bool check_break, bool check_continue) {
    if(operand_->isIdentifier()) {
        golite::PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(operand_);
        golite::Identifier* identifier = static_cast<Identifier*>(primary_expression->lastChild());
        if(identifier->isBlank()) {
            golite::Utils::error_message("Unary operand cannot be a blank identifier", operand_->getLine());
        }
    }
    operand_->weedingPass(check_break, check_continue);
}