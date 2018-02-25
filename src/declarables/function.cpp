#include <golite/function.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Function::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "func ";
    // FIXME Complete this
    return ss.str();
}
