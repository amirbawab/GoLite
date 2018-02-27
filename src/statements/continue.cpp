#include <golite/continue.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Continue::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "continue;";
    return ss.str();
}