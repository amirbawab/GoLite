#include <golite/primary.h>
#include <golite/utils.h>
#include <sstream>

void golite::Primary::addChild(golite::Expression *child) {
    children_.push_back(child);
}

std::string golite::Primary::toGoLite(int indent) {
    std::stringstream ss;
    for(Expression* primary : children_) {
        ss << primary << std::endl;
    }
    return ss.str();
}