#include <golite/type.h>
#include <sstream>
#include <golite/utils.h>
#include <golite/type_reference.h>

std::string golite::Type::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "type " << identifier_->toGoLite(0) << " "
       << type_component_->toGoLite(indent) << ";";
    return ss.str();
}

int golite::Type::getLine() {
    return identifier_->getLine();
}

void golite::Type::weedingPass(bool, bool) {
    identifier_->weedingPass();
    type_component_->weedingPass();
}

void golite::Type::typeCheck() {
    // Do nothing
}

void golite::Type::symbolTablePass(SymbolTable *root) {
    if(root->hasSymbol(this->identifier_->getName(), false)) {
        golite::Utils::error_message("Type name " + identifier_->getName() + " redeclared in this block", getLine());
    }

    if(!identifier_->isBlank()) {
        root->putSymbol(this->identifier_->getName(), this);
        identifier_->symbolTablePass(root);
        type_component_->symbolTablePass(root);

        // Check for recursion
        if(isRecursive()) {
            golite::Utils::error_message("Type " + identifier_->getName() + " cannot be recursive", identifier_->getLine());
        }
    } else {
        type_component_->symbolTablePass(root);
    }
}

std::string golite::Type::toPrettySymbol() {
    std::stringstream ss;
    ss << identifier_->getName() << " [type] = " << type_component_->toPrettySymbol();
    return ss.str();
}

golite::Type::Type(Identifier *identifier, TypeComponent *type_component) {
    identifier_ = identifier;
    type_component_ = type_component;
}

bool golite::Type::isRecursive() {
    return type_component_->isRecursive(this);
}

golite::TypeComponent* golite::Type::toTypeComponent() {
    TypeReference* type_reference = new TypeReference();
    type_reference->setIdentifier(getIdentifier());
    type_reference->setDeclarableType(this);
    TypeComponent* type_component = new TypeComponent();
    type_component->addChild(type_reference);
    return type_component;
}

bool golite::Type::isSelfReferring() {
    for(TypeComposite* type_composite : type_component_->getChildren()) {
        if(type_composite->isRecursive(this)) {
            return true;
        }
    }
    return false;
}

std::string golite::Type::toTypeScript(int indent) {
    std::stringstream ss;
    std::stringstream ss_pre;
    std::stringstream ss_post;
    static long count = 1;
    if(!identifier_->isBlank()) {
        ss_post << type_component_->toTypeScriptInitializer(indent);
        ss_post << golite::Utils::blockComment({"Type " + identifier_->getName() + " was renamed to "
                                           + identifier_->toTypeScript(0)},
                                          indent, identifier_->getLine()) << std::endl;
        ss_post << golite::Utils::indent(indent) << "type " << identifier_->toTypeScript(0) << " = ";
        if(isSelfReferring()) {
            std::string class_name = "self_" + std::to_string(count++);
            ss_pre << golite::Utils::blockComment({"Class solving circular type declaration"}, indent, getLine())
                   << std::endl << golite::Utils::indent(indent) << "class " << class_name << " extends "
                   << type_component_->toTypeScript(0) << " {};" << std::endl << std::endl;
            ss_post << class_name;
        } else {
            ss_post << type_component_->toTypeScript(indent);
        }
        ss_post << ";";
    } else {
        ss_post << golite::Utils::codeNotGenerated(toGoLite(0), indent, getLine());
    }
    ss_post << std::endl;
    ss << ss_pre.str() << ss_post.str();
    return ss.str();
}