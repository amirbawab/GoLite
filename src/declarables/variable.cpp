#include <golite/variable.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <iostream>
#include <vector>

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

void golite::Variable::symbolTablePass(SymbolTable *root) {
    for(std::vector<golite::Identifier*>::iterator itt = this->identifiers_.begin();
            itt != this->identifiers_.end();
            itt++) {
        // search for an existing symbol in current scope
        golite::Declarable* existingSymbol = root->getSymbol((*itt)->getName(), false);
        if(existingSymbol) {
            golite::Utils::error_message((*itt)->getName() + " redeclared in this block", this->getLine());
        }

        root->putSymbol((*itt)->getName(), this);
    }
}