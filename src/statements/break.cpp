#include <golite/break.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Break::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "break;";
    return ss.str();
}

void golite::Break::weedingPass(bool check_break, bool) {
    if(check_break) {
        golite::Utils::error_message("Break statement used outside for loop and switch case", getLine());
    }
}

void golite::Break::typeCheck() {
    // Do nothing
}

void golite::Break::symbolTablePass(SymbolTable *root) {
    // Do nothing
}