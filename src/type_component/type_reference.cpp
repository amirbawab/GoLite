#include <golite/type_reference.h>
#include <sstream>

std::string golite::TypeReference::toGoLite(int indent) {
    std::stringstream ss;
    ss << identifier_->toGoLite(0);
    return ss.str();
}