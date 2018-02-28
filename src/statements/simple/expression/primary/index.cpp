#include <golite/index.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>

std::string golite::Index::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "[" << expression_->toGoLite(0) << "]";
    return ss.str();
}

int golite::Index::getLine() {
    return expression_->getLine();
}

void golite::Index::weedingPass(bool check_break, bool check_continue) {
    if(expression_->isIdentifier()) {
        golite::PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(expression_);
        golite::Identifier* identifier = static_cast<Identifier*>(primary_expression->lastChild());
        if(identifier->isBlank()) {
            golite::Utils::error_message("Index expression cannot be a blank identifier", expression_->getLine());
        }
    }
    expression_->weedingPass(check_break, check_continue);
}