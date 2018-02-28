#include <golite/variable.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::Variable::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "var " << golite::Pretty::implodeIdentifiers(identifiers_);
    if(type_component_) {
        ss << " " << type_component_->toGoLite(indent);
    }
    if(!expressions_.empty()) {
        ss << " = ";
    }
    ss << golite::Pretty::implodeExpressions(expressions_) << ";";
    return ss.str();
}

int golite::Variable::getLine() {
    if(identifiers_.empty()) {
        throw std::runtime_error("Cannot get line number of variable with no identifiers");
    }
    return identifiers_.front()->getLine();
}

void golite::Variable::weedingPass(bool check_break, bool check_continue) {
    if(!expressions_.empty() && identifiers_.size() != expressions_.size()) {
        golite::Utils::error_message("Number of left and right elements of variable declaration does not match",
                                     getLine());
    }

    if(type_component_) {
        type_component_->weedingPass(check_break, check_continue);
    }

    for(Identifier* identifier : identifiers_) {
        identifier->weedingPass(check_break, check_continue);
    }

    for(Expression* expression : expressions_) {
        if(expression->isIdentifier()) {
            golite::Identifier* identifier = static_cast<Identifier*>(expression);
            if(identifier->isBlank()) {
                golite::Utils::error_message("Variable value cannot be a blank identifier", expression->getLine());
            }
        }
        expression->weedingPass(check_break, check_continue);
    }
}