#include <golite/function_call.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>

std::string golite::FunctionCall::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "(" << golite::Pretty::implodeExpressions(args_) << ")";
    return ss.str();
}

void golite::FunctionCall::weedingPass(bool check_break, bool check_continue) {
    for(Expression* expression : args_) {
        if(expression->isIdentifier()) {
            golite::PrimaryExpression* primary_expression = static_cast<PrimaryExpression*>(expression);
            golite::Identifier* identifier = static_cast<Identifier*>(primary_expression->lastChild());
            if(identifier->isBlank()) {
                golite::Utils::error_message("Function call does not accept blank identifier as argument",
                                             expression->getLine());
            }
        }
        expression->weedingPass(check_break, check_continue);
    }
}