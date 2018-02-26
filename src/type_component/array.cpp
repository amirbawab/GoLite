#include <golite/array.h>
#include <sstream>

std::string golite::Array::toGoLite(int indent) {
    std::stringstream ss;
    ss << "[" << size_->toGoLite(0) << "]";
    return ss.str();
}