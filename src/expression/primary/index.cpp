#include <golite/index.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>

std::string golite::Index::toGoLite(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << "[" << expression_->toGoLite(0) << "]";
    return ss.str();
}

int golite::Index::getLine() {
    return expression_->getLine();
}

void golite::Index::weedingPass() {
    if(expression_->isBlank()) {
        golite::Utils::error_message("Index expression cannot be a blank identifier", expression_->getLine());
    }
    expression_->weedingPass();
}

golite::TypeComponent* golite::Index::typeCheck() {
    TypeComponent* expresstion_type = expression_->typeCheck();
    if(!expresstion_type->resolvesToInt()) {
        golite::Utils::error_message("Index expression must resolve to an int", expression_->getLine());
    }
    return nullptr;
}

void golite::Index::symbolTablePass(SymbolTable *root) {
    expression_->symbolTablePass(root);
}