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
    TypeComponent* left_expression_type = left_expression_->typeCheck();
    TypeComponent* right_expression_type = right_expression_->typeCheck();
    std::vector<TypeComposite*> left_children = left_expression_type->getChildren();
    std::vector<TypeComposite*> right_children = right_expression_type->getChildren();
    if(left_children.size() != 2 || !left_children[1]->isSlice()) {
        golite::Utils::error_message("Append statement expects slice type as first argument but given "
                                     + left_expression_type->toGoLiteMin(), left_children[1]->getLine());
    }
    if(right_children.size() != 1 || !left_children[0]->isCompatible(right_children[0])) {
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