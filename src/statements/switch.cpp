#include <golite/switch.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/declaration.h>

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

void golite::Switch::weedingPass(bool check_break, bool check_continue) {
    if(simple_) {
        simple_->weedingPass(check_break, check_continue);
    }
    if(expression_) {
        expression_->weedingPass(check_break, check_continue);
    }

    bool has_default = false;
    for(SwitchCase* switch_case : cases_) {
        if(switch_case->isDefault()) {
            if(has_default) {
                golite::Utils::error_message("Switch statement has more than one default case",
                                             switch_case->getLine());
            }
            has_default = true;
        }
        switch_case->weedingPass(check_break, check_continue);
    }
}