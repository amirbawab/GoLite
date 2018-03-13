#include <golite/type_factory.h>
#include <golite/identifier.h>
#include <golite/type_reference.h>

golite::Type* golite::TypeFactory::createBuiltInType(std::string id) {
    golite::Identifier* type_id = new golite::Identifier(id, -1);

    // Create the built-in type reference
    golite::TypeReference* type_ref = new golite::TypeReference();
    type_ref->setIdentifier(type_id);

    // Create the type component to hold the type refence
    golite::TypeComponent* type_component = new golite::TypeComponent();
    type_component->addChild(type_ref);

    // Build the recursive definition of type_reference -> type
    Type* built_in_type = new Type(type_id, type_component);
    built_in_type->setBuiltIn(true);
    type_ref->setDeclarableType(built_in_type);
    return built_in_type;
}