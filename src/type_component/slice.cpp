#include <golite/slice.h>
#include <sstream>

std::string golite::Slice::toGoLite(int indent) {
    std::stringstream ss;
    ss << "[]" << type_component_->toGoLite(indent);
    return ss.str();
}