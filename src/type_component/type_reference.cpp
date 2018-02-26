#include <golite/type_reference.h>
#include <sstream>

std::string golite::TypeReference::toGoLite(int indent) {
    return identifier_->toGoLite(indent);
}