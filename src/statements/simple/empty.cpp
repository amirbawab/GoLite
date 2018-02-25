#include <golite/empty.h>
#include <golite/utils.h>
#include <sstream>

std::string golite::Empty::toGoLite(int indent) {
    return "/*Empty statement*/;";
}