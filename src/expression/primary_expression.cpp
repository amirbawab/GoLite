#include <golite/primary_expression.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>

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
    return children_.back()->isIdentifier();
}

bool golite::PrimaryExpression::isBlank() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot check if primary expression is a blank identifier because children list is empty");
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
    std::vector<golite::TypeComposite*> type_composites = children_.front()->typeCheck()->getChildren();
    // TODO Traverse the vector of type composite and verify the element in the primary expression align with the type
    return children_.front()->typeCheck();
}

void golite::PrimaryExpression::symbolTablePass(SymbolTable *root) {
    // FIXME Some cases, like selector, would need different symbol table to have a correct lookup
    for(Primary* primary : this->children_) {
        primary->symbolTablePass(root);
    }
}
