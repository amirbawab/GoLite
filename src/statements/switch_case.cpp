#include <golite/switch_case.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::SwitchCase::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent);
    if(isDefault()) {
        ss << "default:";
    } else {
        ss << "case ";
        for(size_t i = 0; i < expressions_.size(); i++) {
            if(i != 0) {
                ss << ", ";
            }
            ss << expressions_[i]->toGoLite(0);
        }
        ss << ":";
    }
    for(Statement* statement : statements_) {
        ss << std::endl << statement->toGoLite(indent+1);
    }
    return ss.str();
}