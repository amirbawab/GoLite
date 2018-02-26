#include <golite/primary.h>
#include <golite/utils.h>
#include <sstream>

void golite::Primary::addChild(golite::Expression *child) {
    children_.push_back(child);
}

std::string golite::Primary::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent);
    for(Expression* primary : children_) {
        ss << primary->toGoLite(0);
    }
    return ss.str();
}

int golite::Primary::getLine() {
    if(children_.empty()) {
        throw std::runtime_error("Cannot get line number of an empty primary");
    }
    return children_.front()->getLine();
}