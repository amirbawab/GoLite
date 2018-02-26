#include <golite/switch.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Switch::toGoLite(int indent) {
    std::stringstream ss;

    // Switch statement
    ss << golite::Utils::indent(indent) << "switch";
    if(simple_) {
        ss << " " << simple_->toGoLite(0) << ";";
    }
    if(expression_) {
        ss << " " << expression_->toGoLite(0);
    }
    ss << " {";

    // Cases
    if(!cases_.empty()) {
        ss << std::endl;
        for(SwitchCase* switch_case : cases_) {
            ss << switch_case->toGoLite(indent+1) << std::endl;
        }
        ss << golite::Utils::indent(indent);
    }
    ss << "}";
    return ss.str();
}