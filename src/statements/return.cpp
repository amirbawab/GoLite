#include <golite/return.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Return::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "return";
    if(expression_) {
        ss << " (" << expression_->toGoLite(0) << " )" << std::endl;
    }
    ss << ";";
    return ss.str();
}
