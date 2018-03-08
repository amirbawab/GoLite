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
        expression->weedingPass();
    }

    for(Expression* expression : right_expressions_) {
        if(expression->isBlank()) {
            golite::Utils::error_message("Declaration value cannot be a blank identifier", expression->getLine());
        }
        expression->weedingPass();
    }
}

void golite::Declaration::typeCheck() {
    for(Expression* expression : right_expressions_) {
        TypeComponent* type_component = expression->typeCheck();
        // TODO Check specs
    }
}

void golite::Declaration::symbolTablePass(SymbolTable *root) {

    if(left_identifiers_.size() != right_expressions_.size()) {
        throw std::runtime_error("Wrong number of left and right elements. Verify weeding pass.");
    }

    bool new_var = false;
    for(size_t i=0; i < left_identifiers_.size(); i++) {

        if(!left_identifiers_[i]->isIdentifier()) {
            throw std::runtime_error("Symbol table expects all left expression to be identifiers. Verify weeding pass.");
        }

        // Skip blank identifiers
        if(!left_identifiers_[i]->isBlank()) {
            golite::PrimaryExpression* id_prim = static_cast<golite::PrimaryExpression*>(left_identifiers_[i]);
            golite::Identifier* id = static_cast<golite::Identifier*>(id_prim->getChildren().back());
            Declarable* existing_dec = root->getSymbol(id->getName(), false);
            if(existing_dec) {
                if(existing_dec->isTypeDeclaration()) {
                    golite::Utils::error_message("Type " + id->getName() + " is not an expression",
                                                 left_identifiers_[i]->getLine());
                }
            } else {
                new_var = true;

                // FIXME Issue #39
                golite::Variable* var_decl = new golite::Variable();
                std::vector<golite::Identifier*> identifiers = { id };
                std::vector<golite::Expression*> expressions = { right_expressions_[i] };
                var_decl->setIdentifiers(identifiers);
                var_decl->setExpressions(expressions);
                root->putSymbol(id->getName(), var_decl);
                // Note: Variable type is determined during type checking pass
            }
        }
    }

    // make sure there's at least one new variable
    if(!new_var) {
        golite::Utils::error_message("no new variables on left side of :=", this->getLine());
    }
}