#include <golite/declaration.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::Declaration::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << golite::Pretty::implodeExpressions(left_identifiers_)
       << " := " << golite::Pretty::implodeExpressions(right_expressions_);
    return ss.str();
}

bool golite::Declaration::badEquation() {
    return left_identifiers_.size() != right_expressions_.size();
}

bool golite::Declaration::badIdentifiers() {
    for(Expression* expression : left_identifiers_) {
        if(!expression->isIdentifier()) {
            return true;
        }
    }
    return false;
}

int golite::Declaration::getLine() {
    if(left_identifiers_.empty()) {
        throw std::runtime_error("Cannot get line of declaration with not left expressions");
    }
    return left_identifiers_.front()->getLine();
}