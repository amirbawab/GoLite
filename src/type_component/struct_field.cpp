#include <golite/struct_field.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::StructField::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent);
    for(size_t i = 0; i < identifiers_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << identifiers_[i]->toGoLite(0);
    }
    ss << " " << type_component_->toGoLite(indent) << ";";
    return ss.str();
}