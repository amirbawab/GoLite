#include <golite/inc_dec.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::IncDec::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << expression_->toGoLite(0);
    if(isIncrement()) {
        ss << "++;";
    } else {
        ss << "--;";
    }
    return ss.str();
}