#include <golite/variable.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <iostream>

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

void golite::Variable::weedingPass(bool, bool) {
    if(!expressions_.empty() && identifiers_.size() != expressions_.size()) {
        golite::Utils::error_message("Number of left and right elements of variable declaration does not match",
                                     getLine());
    }

    if(type_component_) {
        type_component_->weedingPass();
    }

    for(Identifier* identifier : identifiers_) {
        identifier->weedingPass(false, false);
    }

    for(Expression* expression : expressions_) {
        if(expression->isBlank()) {
            golite::Utils::error_message("Variable value cannot be a blank identifier", expression->getLine());
        }
        expression->weedingPass(false, false);
    }
}

golite::TypeComponent* golite::Variable::typeCheck() {
    if(!expressions_.empty()) {
        if(identifiers_.size() != expressions_.size()) {
            throw std::runtime_error("Cannot perform type checking on variable statement with different number of "
                                             "identifiers and expressions");
        }

        for(size_t i=0; i < identifiers_.size(); i++) {
            TypeComponent* type_component = expressions_[i]->typeCheck();
            // TODO type_component_ == type_component
        }
    }
    return nullptr;
}