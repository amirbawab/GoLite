#include <golite/array.h>
#include <sstream>

std::string golite::Array::toGoLite(int indent) {
    std::stringstream ss;
    ss << "[" << size_->toGoLite(0) << "]";
    return ss.str();
}

int golite::Array::getLine() {
    return size_->getLine();
}

void golite::Array::weedingPass() {
    size_->weedingPass(false, false);
}