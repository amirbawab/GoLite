#include <golite/declaration.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Declaration::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent);
    for(size_t i = 0; i < left_identifiers_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << left_identifiers_[i]->toGoLite(0);
    }
    ss << " := ";
    for(size_t i = 0; i < right_expressions_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << right_expressions_[i]->toGoLite(0);
    }
    ss << ";";
    return ss.str();
}

void golite::Declaration::setIdentifiers(std::vector<golite::Expression *> identifiers) {
    // TODO Make sure expressions are identifiers (not arrays, function calls nor selectors)
    left_identifiers_ = identifiers;
}