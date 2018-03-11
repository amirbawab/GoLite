#include <golite/primary_expression.h>
#include <golite/utils.h>
#include <golite/identifier.h>
#include <sstream>
#include <iostream>

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
    Declarable* declarable = nullptr;
    std::vector<golite::TypeComposite*> type_composites;
    for(size_t i=0; i < children_.size(); i++) {

        // Get child type information
        Primary* child = children_[i];
        TypeComponent* child_type = child->typeCheck();
        std::vector<TypeComposite*> child_type_children = child_type->getChildren();

        // TODO
        if(child->isSelector()) {

        } else if(child->isIdentifier()) {
            type_composites.insert(type_composites.end(), child_type_children.begin(), child_type_children.end());
        } else if(child->isLiteral()) {

        } else if(child->isIndex()) {

        } else if(child->isFunctionCall()) {

        } else if(child->isAppend()) {

        } else if(child->isParenthesis()) {

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
