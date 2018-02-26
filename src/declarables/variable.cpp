#include <golite/variable.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Variable::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "var ";
    for(size_t i=0; i < identifiers_.size(); i++) {
        if (i != 0) {
            ss << ", ";
        }
        ss << identifiers_[i]->toGoLite(0);
    }

    if(type_component_) {
        ss << " " << type_component_->toGoLite(indent);
    }

    if(!expressions_.empty()) {
        ss << " = ";
    }
    for(size_t i = 0; i < expressions_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << expressions_[i]->toGoLite(0);
    }
    ss << ";";
    return ss.str();
}