#include <golite/empty.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Empty::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "/*empty*/";
    return ss.str();
}