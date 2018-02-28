#include <golite/println.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>

std::string golite::Println::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "println(" << golite::Pretty::implodeExpressions(expressions_) << ");";
    return ss.str();
}

void golite::Println::weedingPass(bool check_break, bool check_continue) {
    for(Expression* expression : expressions_) {
        if(expression->isIdentifier()) {
            golite::PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(expression);
            golite::Identifier* identifier = static_cast<Identifier*>(primary_expression->lastChild());
            if(identifier->isBlank()) {
                golite::Utils::error_message("Function println does not accept blank identifier as arguments",
                                             expression->getLine());
            }
        }
        expression->weedingPass(check_break, check_continue);
    }
}