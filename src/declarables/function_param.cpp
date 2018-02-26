#include <golite/function_param.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::FunctionParam::toGoLite(int indent) {
    std::stringstream ss;
    for(size_t i=0; i < identifiers_.size(); i++) {
        if (i != 0) {
            ss << ", ";
        }
        ss << identifiers_[i]->toGoLite(0);
    }
    ss << " " << type_component_->toGoLite(0);
    return ss.str();
}