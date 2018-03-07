#include <golite/function_call.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>

std::string golite::FunctionCall::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "(" << golite::Pretty::implodeExpressions(args_) << ")";
    return ss.str();
}

void golite::FunctionCall::weedingPass(bool, bool) {
    for(Expression* expression : args_) {
        if(expression->isBlank()) {
            golite::Utils::error_message("Function call does not accept blank identifier as argument",
                                         expression->getLine());
        }
        expression->weedingPass(false, false);
    }
}

void golite::FunctionCall::symbolTablePass(SymbolTable *root) {
    for(Expression* expr : this->args_) {
        expr->symbolTablePass(root);
    }
}