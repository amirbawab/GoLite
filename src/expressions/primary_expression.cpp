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

void golite::PrimaryExpression::weedingPass(bool check_break, bool check_continue) {
    if(children_.empty()) {
        throw std::runtime_error("Cannot perform weeding pass on primary expression because children list is empty");
    }

    if(children_.front()->isIdentifier()){
        golite::Identifier* identifier = static_cast<Identifier*>(children_.front());
        if(identifier->isBlank() && children_.size() > 1) {
            golite::Utils::error_message("Blank identifier cannot be accessed", getLine());
        }
    }

    for(Primary* primary : children_) {
        primary->weedingPass(check_break, check_continue);
    }
}

golite::Primary* golite::PrimaryExpression::lastChild() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot get last child of an empty list");
    }
    return children_.back();
}