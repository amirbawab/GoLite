#include <golite/slice.h>
#include <sstream>

std::string golite::Slice::toGoLite(int indent) {
    std::stringstream ss;
    ss << "[]";
    return ss.str();
}

void golite::Slice::weedingPass() {
    // Do nothing
}

void golite::Slice::symbolTablePass(SymbolTable *root) {
    // Do nothing
}