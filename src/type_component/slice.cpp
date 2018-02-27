#include <golite/slice.h>
#include <sstream>

std::string golite::Slice::toGoLite(int indent) {
    std::stringstream ss;
    ss << "[]";
    return ss.str();
}