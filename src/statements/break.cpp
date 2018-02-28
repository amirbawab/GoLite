#include <golite/break.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Break::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "break;";
    return ss.str();
}

void golite::Break::weedingPass(bool check_break, bool check_continue) {
    if(check_break) {
        golite::Utils::error_message("Break statement used outside for loop and switch case", getLine());
    }
}