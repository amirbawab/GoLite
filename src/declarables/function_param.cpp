#include <golite/function_param.h>
#include <golite/utils.h>
#include <golite/pretty_helper.h>

std::string golite::FunctionParam::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << golite::Pretty::implodeIdentifiers(identifiers_)
       << " " << type_component_->toGoLite(0);
    return ss.str();
}