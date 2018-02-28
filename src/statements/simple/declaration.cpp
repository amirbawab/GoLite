#include <golite/declaration.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::Declaration::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << golite::Pretty::implodeExpressions(left_identifiers_)
       << " := " << golite::Pretty::implodeExpressions(right_expressions_);
    return ss.str();
}

int golite::Declaration::getLine() {
    if(left_identifiers_.empty()) {
        throw std::runtime_error("Cannot get line of declaration with not left expressions");
    }
    return left_identifiers_.front()->getLine();
}

void golite::Declaration::weedingPass(bool check_break, bool check_continue) {
    if(left_identifiers_.size() != right_expressions_.size()) {
        golite::Utils::error_message("Number of left and right elements of declaration does not match", getLine());
    }

    for(Expression* expression : left_identifiers_) {
        if(!expression->isIdentifier()) {
            golite::Utils::error_message("Element to the left of the declaration must be identifiers",
                                         expression->getLine());
        }
    }

    for(Expression* expression : right_expressions_) {
        if(expression->isIdentifier()) {
            golite::Identifier* identifier = static_cast<Identifier*>(expression);
            if(identifier->isBlank()) {
                golite::Utils::error_message("Declaration value cannot be a blank identifier", expression->getLine());
            }
        }
        expression->weedingPass(check_break, check_continue);
    }
}
