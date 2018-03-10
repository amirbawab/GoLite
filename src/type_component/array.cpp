#include <golite/array.h>
#include <sstream>

std::string golite::Array::toGoLite(int indent) {
    std::stringstream ss;
    ss << "[" << size_->toGoLite(0) << "]";
    return ss.str();
}

std::string golite::Array::toGoLiteMin() {
    return toGoLite(0);
}

int golite::Array::getLine() {
    return size_->getLine();
}

void golite::Array::weedingPass() {
    size_->weedingPass();
}

void golite::Array::symbolTablePass(SymbolTable *root) {
    // Do nothing
}

bool golite::Array::isCompatible(TypeComposite *type_composite) {
    // TODO
    return true;
}