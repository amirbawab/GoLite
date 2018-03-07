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
 * Declaration are treated like shorthand for variable declarations
 */
void golite::Declaration::symbolTablePass(SymbolTable *root) {
    for(golite::Expression* expr : this->right_expressions_) {
        expr->symbolTablePass(root);
    }

    std::vector<golite::Identifier*> new_vars = std::vector<golite::Identifier*>();
    for(int i = 0; i < this->left_identifiers_.size(); i++) {
        golite::PrimaryExpression* id_prim = static_cast<golite::PrimaryExpression*>(this->left_identifiers_[i]);
        if(id_prim->isIdentifier()) {
            golite::Identifier* id = static_cast<golite::Identifier*>(id_prim->getChildren().back());

            golite::Declarable* already_declared_var = root->getSymbol(id->getName(), false);
            if(already_declared_var) {
                this->right_expressions_.erase(this->right_expressions_.begin() + i);

                // TODO : check if we need to replace the existing variable ? not sure issue #35
                /*// somehow re-assign the new expression to the already declared variable
                if(already_declared_var->isDecVariable()) {
                    golite::Variable* existing_var = static_cast<golite::Variable*>(already_declared_var);
                    long indexof_id = existing_var->indexOfIdentifier(id->getName());
                    existing_var->replaceExpression(indexof_id, this->right_expressions_[indexof_id]); // overwrite the variable with new value

                    // then remove from the right_expression as they are now not new variables

                }*/
            } else {
                new_vars.push_back(id);
            }
        }
    }

    // make sure there's at least one new variable
    if(new_vars.size() == 0) {
        golite::Utils::error_message("no new variables on left side of :=", this->getLine());
    }

    golite::Variable* var_decl = new golite::Variable();
    var_decl->setIdentifiers(new_vars);
    var_decl->setExpressions(this->right_expressions_);

    var_decl->symbolTablePass(root);
}