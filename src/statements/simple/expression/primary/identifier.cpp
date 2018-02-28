#include <golite/identifier.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Identifier::BLANK = "_";

std::string golite::Identifier::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << name_;
    return ss.str();
}

bool golite::Identifier::isBlank() {
    return name_ == BLANK;
}

void golite::Identifier::weedingPass(bool check_break, bool check_continue) {
    // Do nothing
}