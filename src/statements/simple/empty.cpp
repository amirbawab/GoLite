#include <golite/empty.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Empty::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "/*empty*/";
    return ss.str();
}

int golite::Empty::getLine() {
    throw std::runtime_error("Empty statement should not be used to get a line number");
}