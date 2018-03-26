#include <golite/append.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>
#include <iostream>

std::string golite::Append::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "append("
       << left_expression_->toGoLite(0) << ", "
       << right_expression_->toGoLite(0) << ")";
    return ss.str();
}

int golite::Append::getLine() {
    return left_expression_->getLine();
}

void golite::Append::weedingPass() {
    if(left_expression_->isBlank()) {
        golite::Utils::error_message("Append does not accept left argument to be a blank identifier",
                                     left_expression_->getLine());
    }

    if(right_expression_->isBlank()) {
        golite::Utils::error_message("Append does not accept right argument to be a blank identifier",
                                     right_expression_->getLine());
    }

    left_expression_->weedingPass();
    right_expression_->weedingPass();
}

golite::TypeComponent* golite::Append::typeCheck() {
    TypeComponent *left_expression_type = left_expression_->typeCheck();
    TypeComponent *right_expression_type = right_expression_->typeCheck();
    std::vector<TypeComposite *> left_children = left_expression_type->resolveChildren();
    std::vector<TypeComposite *> right_children = right_expression_type->getChildren();
    if (left_children.empty() || !left_children.back()->isSlice()) {
        golite::Utils::error_message("Append statement expects slice type as first argument but given "
                                     + left_expression_type->toGoLiteMin(), getLine());
    }

    // Remove slice
    left_children.pop_back();
    TypeComponent *left_type_component = new TypeComponent(left_children);
    TypeComponent *right_type_component = new TypeComponent(right_children);
    if (!left_type_component->isCompatible(right_type_component)) {
        golite::Utils::error_message("Append statement arguments are not compatible "
                                     + left_expression_type->toGoLiteMin() + " and "
                                     + right_expression_type->toGoLiteMin(), getLine());
    }
    return left_expression_type;
}

void golite::Append::symbolTablePass(SymbolTable *root) {
    this->left_expression_->symbolTablePass(root);
    this->right_expression_->symbolTablePass(root);
}

std::string golite::Append::toTypeScript(int indent) {
    // TODO
    return "";
}

std::string golite::Append::toTypeScriptInitializer(int indent) {
    // TODO
    return "";
}