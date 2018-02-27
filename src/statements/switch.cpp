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

golite::Continue* golite::Switch::badContinue() {
    for(SwitchCase* switch_case : cases_) {
        Continue* bad = switch_case->getBlock()->badContinue();
        if(bad) return bad;
    }
    return nullptr;
}

golite::Statement* golite::Switch::badStatement() {
    for(SwitchCase* switch_case : cases_) {
        Statement* bad = switch_case->getBlock()->badStatement();
        if(bad) return bad;
    }
    return nullptr;
}

golite::Declaration* golite::Switch::badDeclaration() {
    for(SwitchCase* switch_case : cases_) {
        Declaration* bad = switch_case->getBlock()->badDeclaration();
        if(bad) return bad;
    }
    return nullptr;
}
