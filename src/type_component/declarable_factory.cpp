#include <golite/declarable_factory.h>
#include <golite/identifier.h>
#include <golite/type_reference.h>
#include <golite/program.h>

golite::Type* golite::DeclarableFactory::createBuiltInType(std::string id) {
    golite::Identifier* type_id = new golite::Identifier(id, -1);

    // Create the built-in type reference
    golite::TypeReference* type_ref = new golite::TypeReference();
    type_ref->setIdentifier(type_id);

    // Create the type component to hold the type refence
    golite::TypeComponent* type_component = new golite::TypeComponent();
    type_component->addChild(type_ref);

    // Build the recursive definition of type_reference -> type
    Type* built_in_type = new Type(type_id, type_component);
    type_ref->setDeclarableType(built_in_type);
    return built_in_type;
}

golite::Variable* golite::DeclarableFactory::createConstant(std::string id, TypeComponent* type_component) {
    Variable* var = new Variable();
    Identifier* var_id = new Identifier(id, -1);
    var->setTypeComponent(type_component);
    var->setIdentifiers({var_id});
    var->setConstant(true);
    return var;
}