#include <golite/print.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::Print::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "print(" << golite::Pretty::implodeExpressions(expressions_) << ");";
    return ss.str();
}