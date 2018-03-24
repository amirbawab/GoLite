#include <golite/simple_expression.h>
#include <golite/utils.h>
#include <sstream>
#include <golite/primary_expression.h>
#include <golite/parenthesis.h>
#include <iostream>

int golite::SimpleExpression::getLine() {
    return expression_->getLine();
}

void golite::SimpleExpression::typeCheck() {
    expression_->typeCheck();
    if(expression_->isCasting()) {
        golite::Utils::error_message("Expression statement must be a function call but given conversion",
                                     expression_->getLine());
    }
}

void golite::SimpleExpression::weedingPass(bool, bool) {
    expression_->weedingPass();
    Expression* resolved_expression = expression_->resolveExpression();
    if(!resolved_expression->isFunctionCall()) {
        golite::Utils::error_message("Expression statement must be a function call", expression_->getLine());
    }
}

std::string golite::SimpleExpression::toGoLite(int indent) {
    std::stringstream ss;
    ss << expression_->toGoLite(indent) << ";";
    return ss.str();
}

void golite::SimpleExpression::symbolTablePass(SymbolTable *root) {
    this->expression_->symbolTablePass(root);
}

std::string golite::SimpleExpression::toTypeScript(int indent) {
    std::stringstream ss;
    ss << golite::Utils::indent(indent) << expression_->toTypeScript(0) << ";";
    return ss.str();
}