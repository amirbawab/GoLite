#include <golite/slice.h>
#include <sstream>

std::string golite::Slice::toGoLite(int indent) {
    std::stringstream ss;
    ss << "[]";
    return ss.str();
}

std::string golite::Slice::toGoLiteMin() {
    return toGoLite(0);
}

void golite::Slice::weedingPass() {
    // Do nothing
}

void golite::Slice::symbolTablePass(SymbolTable *root) {
    // Do nothing
}

bool golite::Slice::isCompatible(TypeComposite *type_composite) {
    // TODO
    return true;
}