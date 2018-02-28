#include <golite/continue.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Continue::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "continue;";
    return ss.str();
}

void golite::Continue::weedingPass(bool check_break, bool check_continue) {
    if(check_continue) {
        golite::Utils::error_message("Continue statement used outside for loop", getLine());
    }
}