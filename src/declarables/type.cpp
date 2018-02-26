#include <golite/type.h>
#include <sstream>

std::string golite::Type::toGoLite(int indent) {
    std::stringstream ss;
    ss << "type " << type_component_->toGoLite(indent);
    return ss.str();
}