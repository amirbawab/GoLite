#include <golite/primary_expression.h>
#include <golite/utils.h>
#include <golite/identifier.h>
#include <sstream>
#include <iostream>
#include <golite/selector.h>
#include <golite/parenthesis.h>

void golite::PrimaryExpression::addChild(golite::Primary *child) {
    children_.push_back(child);
}

std::string golite::PrimaryExpression::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent);
    for(Expression* primary : children_) {
        ss << primary->toGoLite(0);
    }
    return ss.str();
}

int golite::PrimaryExpression::getLine() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot get line number of an empty primary");
    }
    return children_.front()->getLine();
}

bool golite::PrimaryExpression::isFunctionCall() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if primary expression is a function call because children list is empty");
    }
    return children_.back()->isFunctionCall();
}

bool golite::PrimaryExpression::isIdentifier() {
    // TODO Check if we can resolve inside parenthesis. Refactor required if applied
    // TODO Or maybe create another method called resolvesToIdentifier()
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if primary expression is an identifier because children list is empty");
    }
    if(children_.size() != 1) {
        return false;
    }
    return children_.back()->isIdentifier();
}

bool golite::PrimaryExpression::isBlank() {
    if(!isIdentifier()) {
        return false;
    }
    return children_.back()->isBlank();
}

void golite::PrimaryExpression::weedingPass() {
    if (children_.empty()) {
        throw std::runtime_error("Cannot perform weeding pass on primary expression because children list is empty");
    }

    if (children_.front()->isBlank() && children_.size() > 1) {
        golite::Utils::error_message("Blank identifier cannot be accessed", children_.front()->getLine());
    }

    for (Primary *primary : children_) {
        primary->weedingPass();
    }
}

golite::TypeComponent* golite::PrimaryExpression::typeCheck() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot perform type checking on a primary expression with an empty list of children");
    }

    // Get the type of the first element
    Expression* base_expression = nullptr;
    std::vector<golite::TypeComposite*> type_composites;
    for(size_t i = 0; i < children_.size(); i++) {
        TypeComponent* child_type = children_[i]->typeCheck();
        if(children_[i]->isSelector()) {
            base_expression = children_[i];
        } else if(children_[i]->isIdentifier()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            type_composites.insert(type_composites.end(), type_children.begin(), type_children.end());
            base_expression = children_[i];
        } else if(children_[i]->isLiteral()) {
            std::vector<TypeComposite*> type_children = child_type->getChildren();
            base_expression = children_[i];
        } else if(children_[i]->isIndex()) {
        } else if(children_[i]->isFunctionCall()) {
        } else if(children_[i]->isAppend()) {
            base_expression = children_[i];
        } else if(children_[i]->isParenthesis()) {
            base_expression = children_[i];
        } else {
            throw std::runtime_error("Unhandled type check for an unrecognized child type");
        }
    }
    // TODO Traverse the vector of type composite and verify the element in the primary expression align with the type
    return children_.front()->typeCheck();
}

void golite::PrimaryExpression::symbolTablePass(SymbolTable *root) {
    if(children_.empty()) {
        throw std::runtime_error("Cannot perform symbol table pass on a primary expression with an empty list of children");
    }
    children_.front()->symbolTablePass(root);
    // The rest of the primary expression children are handled by the type checking pass
}

bool golite::PrimaryExpression::isParenthesis() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if primary expression is a parenthesis because children list is empty");
    }
    if(children_.size() != 1) {
        return false;
    }
    return children_.back()->isParenthesis();
}