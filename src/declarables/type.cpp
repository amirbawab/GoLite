#include <golite/type.h>
#include <sstream>
#include <golite/utils.h>

std::string golite::Type::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "type " << identifier_->toGoLite(0) << " "
       << type_component_->toGoLite(indent) << ";";
    return ss.str();
}