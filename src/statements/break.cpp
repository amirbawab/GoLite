#include <golite/break.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Break::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "break;";
    return ss.str();
}