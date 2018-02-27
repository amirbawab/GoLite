#include <golite/declaration.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::Declaration::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << golite::Pretty::implodeExpressions(left_identifiers_)
       << " := " << golite::Pretty::implodeExpressions(right_expressions_);
    return ss.str();
}

void golite::Declaration::setIdentifiers(std::vector<golite::Expression *> identifiers) {
    // TODO Make sure expressions are identifiers (not arrays, function calls nor selectors)
    left_identifiers_ = identifiers;
}

bool golite::Declaration::badEquation() {
    return left_identifiers_.size() != right_expressions_.size();
}