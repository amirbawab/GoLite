#include <golite/identifier.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Identifier::toGoLite(int indent) {
    return name_;
}