#include <golite/slice.h>
#include <sstream>

std::string golite::Slice::toGoLite(int indent) {
    std::stringstream ss;
    ss << "[]";
    return ss.str();
}

void golite::Slice::weedingPass(bool check_break, bool check_continue) {
    // Do nothing
}