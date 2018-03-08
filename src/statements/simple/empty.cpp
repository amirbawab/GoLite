#include <golite/empty.h>
#include <sstream>

std::string golite::Empty::toGoLite(int indent) {
    return std::string("");
}

int golite::Empty::getLine() {
    throw std::runtime_error("Empty statement should not be used to get a line number");
}

void golite::Empty::weedingPass(bool, bool) {
    // Do nothing
}

void golite::Empty::typeCheck() {
    // Do nothing
}

void golite::Empty::symbolTablePass(SymbolTable *root) {
    // Do nothing
}