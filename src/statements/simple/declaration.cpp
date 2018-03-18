#include <golite/declaration.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>
#include <golite/primary_expression.h>
#include <golite/variable.h>
#include <iostream>
#include <golite/program.h>
#include <set>

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
    if(left_identifiers_.size() != right_expressions_.size()) {
        throw std::runtime_error("Wrong number of left and right elements. Verify weeding pass");
    }

    for(size_t i=0; i < left_identifiers_.size(); i++) {

        if(!left_identifiers_[i]->isIdentifier()) {
            throw std::runtime_error("Declaration in type checking pass expects all left expression to be "
                                             "identifiers. Verify weeding pass.");
        }

        TypeComponent* right_type = right_expressions_[i]->typeCheck();
        if(!left_identifiers_[i]->isBlank()) {
            TypeComponent* left_type = left_identifiers_[i]->typeCheck();
            if(left_type->isInfer()) {
                if(right_type->isVoid()) {
                    golite::Utils::error_message("Short declaration cannot be assigned a void",
                                                 left_identifiers_[i]->getLine());
                }
                if(right_type->isPointer()) {
                    golite::Utils::error_message("Cannot assign " + right_type->toGoLiteMin() + " to a short declaration",
                                                 right_expressions_[i]->getLine());
                }
                golite::PrimaryExpression* id_prim = static_cast<golite::PrimaryExpression*>(left_identifiers_[i]);
                golite::Identifier* id = static_cast<golite::Identifier*>(id_prim->getChildren().back());
                id->updateTypeInSymbolTable(right_type);
            } else if(!left_type->isCompatible(right_type)) {
                golite::Utils::error_message("Element at index " + std::to_string(i)
                                             + " expects an expression of type " + left_type->toGoLiteMin()
                                             + " but given " + right_type->toGoLiteMin(),
                                             right_expressions_[i]->getLine());
            }
        }
    }
}

void golite::Declaration::symbolTablePass(SymbolTable *root) {

    if(left_identifiers_.size() != right_expressions_.size()) {
        throw std::runtime_error("Wrong number of left and right elements. Verify weeding pass.");
    }

    for(Expression* expression : right_expressions_) {
        expression->symbolTablePass(root);
    }

    bool new_var = false;
    std::set<Declarable*> variableSet;
    for(size_t i=0; i < left_identifiers_.size(); i++) {

        if(!left_identifiers_[i]->isIdentifier()) {
            throw std::runtime_error("Declaration in symbol table pass expects all left expression "
                                             "to be identifiers. Verify weeding pass.");
        }

        // Skip blank identifiers
        if(!left_identifiers_[i]->isBlank()) {
            golite::PrimaryExpression* id_prim = static_cast<golite::PrimaryExpression*>(left_identifiers_[i]);
            golite::Identifier* id = static_cast<golite::Identifier*>(id_prim->getChildren().back());
            Declarable* existing_dec = root->getSymbol(id->getName(), false);
            if(!existing_dec) {
                new_var = true;

                // FIXME Issue #39
                golite::Variable* var_decl = new golite::Variable();
                var_decl->setIdentifiers({ id });
                var_decl->setExpressions({ right_expressions_[i] });
                var_decl->setTypeComponent(golite::Program::INFER_TYPE->getTypeComponent());
                root->putSymbol(id->getName(), var_decl);
                existing_dec = var_decl;
            }

            if(variableSet.find(existing_dec) != variableSet.end()) {
                golite::Utils::error_message("Variable " + left_identifiers_[i]->toGoLite(0) + " is repeated",
                                             left_identifiers_[i]->getLine());
            }
            variableSet.insert(existing_dec);
            left_identifiers_[i]->symbolTablePass(root);
        }
    }

    // make sure there's at least one new variable
    if(!new_var) {
        golite::Utils::error_message("no new variables on left side of :=", this->getLine());
    }
}