#include <golite/switch.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Switch::toGoLite(int indent) {
    std::stringstream ss;
    ss << "switch";
    if(simple_) {
        ss << " " << simple_->toGoLite(0) << ";";
    }
    if(expression_) {
        ss << " " << simple_->toGoLite(0);
    }
    ss << " {" << std::endl;
    for(SwitchCase* switch_case : cases_) {
        ss << switch_case->toGoLite(indent) << std::endl;
    }
    ss << golite::Utils::indent(indent) << "}";
    return ss.str();
}