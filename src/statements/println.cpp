#include <golite/println.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::Println::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "println(" << golite::Pretty::implodeExpressions(expressions_) << ");";
    return ss.str();
}
