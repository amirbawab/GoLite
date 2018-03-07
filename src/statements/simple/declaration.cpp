#include <golite/declaration.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>
#include <golite/variable.h>
#include <iostream>

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

void golite::Declaration::weedingPass(bool, bool) {
    if(left_identifiers_.size() != right_expressions_.size()) {
        golite::Utils::error_message("Number of left and right elements of declaration does not match", getLine());
    }

    for(Expression* expression : left_identifiers_) {
        if(!expression->isIdentifier()) {
            golite::Utils::error_message("Element to the left of the declaration must be identifiers",
                                         expression->getLine());
        }
        expression->weedingPass(false, false);
    }

    for(Expression* expression : right_expressions_) {
        if(expression->isBlank()) {
            golite::Utils::error_message("Declaration value cannot be a blank identifier", expression->getLine());
        }
        expression->weedingPass(false, false);
    }
}

/**
 * Declaration are treated like short-end for variable declarations
 */
void golite::Declaration::symbolTablePass(SymbolTable *root) {
    for(golite::Expression* expr : this->left_identifiers_) {
        expr->symbolTablePass(root);
    }

    for(golite::Expression* expr : this->right_expressions_) {
        expr->symbolTablePass(root);
    }

    std::vector<golite::Identifier*> ids = std::vector<golite::Identifier*>();
    for(int i = 0; i < this->left_identifiers_.size(); i++) {
        golite::Identifier* id = static_cast<golite::Identifier*>(this->left_identifiers_[i]);
        ids.push_back(id);
    }

    golite::Variable* var_decl = new golite::Variable();
    var_decl->setIdentifiers(ids);
    var_decl->setExpressions(this->right_expressions_);

    var_decl->symbolTablePass(root);
}