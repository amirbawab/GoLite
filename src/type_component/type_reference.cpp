#include <golite/type_reference.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::TypeReference::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << type_->toGoLite(indent) << std::endl;
    return ss.str();
}