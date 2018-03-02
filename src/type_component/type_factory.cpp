#include <golite/type_factory.h>
#include <golite/identifier.h>
#include <golite/type_reference.h>

const golite::Type golite::TypeFactory::createBuiltInType(std::string id) {
    golite::Identifier* type_id = new golite::Identifier(id, -1);

    golite::TypeReference* type_ref = new golite::TypeReference();
    type_ref->setIdentifier(type_id);

    golite::TypeComponent* type_component = new golite::TypeComponent();
    type_component->addChild(type_ref);

    return golite::Type(type_id, type_component);
}