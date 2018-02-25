#include <golite/struct_field.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::StructField::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << " identifiers "
       << type_component_->toGoLite(indent) << std::endl;
    return ss.str();
}