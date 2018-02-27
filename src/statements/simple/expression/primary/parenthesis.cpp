#include <golite/parenthesis.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Parenthesis::toGoLite(int indent) {
    std::stringstream ss;
    ss << expression_->toGoLite(indent);
    return ss.str();
}

int golite::Parenthesis::getLine() {
    return expression_->getLine();
}