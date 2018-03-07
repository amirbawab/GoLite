#include <golite/parenthesis.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/identifier.h>
#include <golite/primary_expression.h>

std::string golite::Parenthesis::toGoLite(int indent) {
    std::stringstream ss;
    ss << expression_->toGoLite(indent);
    return ss.str();
}

int golite::Parenthesis::getLine() {
    return expression_->getLine();
}

void golite::Parenthesis::weedingPass() {
    if(expression_->isBlank()) {
        golite::Utils::error_message("Blank identifier cannot exist between parenthesis", expression_->getLine());
    }
    expression_->weedingPass();
}

golite::TypeComponent* golite::Parenthesis::typeCheck() {
    return nullptr;
}

void golite::Parenthesis::symbolTablePass(SymbolTable *root) {
    this->expression_->symbolTablePass(root);
}