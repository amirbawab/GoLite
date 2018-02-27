#include <golite/function_call.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::FunctionCall::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "(" << golite::Pretty::implodeExpressions(args_) << ")";
    return ss.str();
}