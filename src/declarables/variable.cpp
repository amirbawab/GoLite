#include <golite/variable.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::Variable::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "var " << golite::Pretty::implodeIdentifiers(identifiers_);
    if(type_component_) {
        ss << " " << type_component_->toGoLite(indent);
    }
    if(!expressions_.empty()) {
        ss << " = ";
    }
    ss << golite::Pretty::implodeExpressions(expressions_) << ";";
    return ss.str();
}

bool golite::Variable::badEquation() {
    if(expressions_.empty()) return false;
    return identifiers_.size() != expressions_.size();
}