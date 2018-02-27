#include <golite/identifier.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Identifier::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << name_;
    return ss.str();
}