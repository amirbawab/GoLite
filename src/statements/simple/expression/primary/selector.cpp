#include <golite/selector.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Selector::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "." << identifier_->toGoLite(0);
    return ss.str();
}
