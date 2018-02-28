#include <golite/print.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::Print::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "print(" << golite::Pretty::implodeExpressions(expressions_) << ");";
    return ss.str();
}

void golite::Print::weedingPass(bool check_break, bool check_continue) {
    for(Expression* expression : expressions_) {
        if(expression->isIdentifier()) {
            golite::Identifier* identifier = static_cast<Identifier*>(expression);
            if(identifier->isBlank()) {
                golite::Utils::error_message("Function print does not accept blank identifier as arguments",
                                             expression->getLine());
            }
        }
        expression->weedingPass(check_break, check_continue);
    }
}
