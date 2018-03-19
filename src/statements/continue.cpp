#include <golite/continue.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Continue::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "continue;";
    return ss.str();
}

void golite::Continue::weedingPass(bool, bool check_continue) {
    if(check_continue) {
        golite::Utils::error_message("Continue statement used outside for loop", getLine());
    }
}

void golite::Continue::typeCheck() {
    // Do nothing
}

void golite::Continue::symbolTablePass(SymbolTable *root) {
    // Do nothing
}

std::string golite::Continue::toTypeScript(int indent) {
    // TODO
    return "";
}