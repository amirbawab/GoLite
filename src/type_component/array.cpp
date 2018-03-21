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
    if(!type_composite->isArray()) {
        return false;
    }
    Array* array = static_cast<Array*>(type_composite);
    return size_->getValue() == array->size_->getValue();
}

std::string golite::Array::toPrettySymbol() {
    return toGoLiteMin();
}

std::vector<golite::TypeComposite*> golite::Array::resolveChildren() {
    return {this};
}

std::string golite::Array::toTypeScript(int indent) {
    throw std::runtime_error("Cannot convert array to typescript");
}