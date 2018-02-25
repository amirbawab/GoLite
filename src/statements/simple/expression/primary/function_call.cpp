#include <golite/function_call.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::FunctionCall::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(0) << "( ";
    for(size_t i = 0; i < args_.size(); i++) {
        if(i != 0) {
            ss << ", ";
        }
        ss << args_[i]->toGoLite(0);
    }
    ss << ")";
    return ss.str();
}