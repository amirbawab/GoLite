#include<golite/cast.h>
#include <sstream>
#include <golite/type_reference.h>

std::string golite::Cast::toGoLite(int indent) {
    return getTypeComponent()->toGoLite(indent);
}

std::string golite::Cast::toGoLiteMin() {
    std::stringstream ss;
    ss << "(<expr>) -> " << getTypeComponent()->toGoLiteMin();
    return ss.str();
}

void golite::Cast::weedingPass() {
    // Do nothing
}

void golite::Cast::symbolTablePass(SymbolTable *root) {
    // Do nothing
}

bool golite::Cast::isCompatible(TypeComposite *type_composite) {
    return false;
}

std::string golite::Cast::toPrettySymbol() {
    return "";
}

std::vector<golite::TypeComposite*> golite::Cast::resolveChildren() {
    return {this};
}

golite::TypeComponent* golite::Cast::getTypeComponent() {
    TypeReference* type_reference = new TypeReference();
    type_reference->setIdentifier(type_->getIdentifier());
    type_reference->setDeclarableType(type_);
    TypeComponent* type_component = new TypeComponent();
    type_component->addChild(type_reference);
    return type_component;
}