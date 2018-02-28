#include <golite/parenthesis.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>

std::string golite::Parenthesis::toGoLite(int indent) {
    std::stringstream ss;
    ss << expression_->toGoLite(indent);
    return ss.str();
}

int golite::Parenthesis::getLine() {
    return expression_->getLine();
}

void golite::Parenthesis::weedingPass(bool check_break, bool check_continue) {
    if(expression_->isIdentifier()) {
        golite::PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(expression_);
        golite::Identifier* identifier = static_cast<Identifier*>(primary_expression->lastChild());
        if(identifier->isBlank()) {
            golite::Utils::error_message("Blank identifier cannot exist between parenthesis", expression_->getLine());
        }
    }
    expression_->weedingPass(check_break, check_continue);
}